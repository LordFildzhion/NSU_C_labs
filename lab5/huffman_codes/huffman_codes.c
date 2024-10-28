#include "./huffman_codes.h"

table_item *table_make()
{
	table_item *table = (table_item *) calloc(BUFFER_SIZE, sizeof(table_item));
	return table;
}

void cleanup(FILE *input, FILE *output, priority_queue *queue, table_item *table, tree_node *root, haff_table *h_table)
{
	fclose(input);
	fclose(output);

	pr_queue_destroy(queue);

	free(table);

	tree_destroy(root);

	free(h_table);

}

uint32_t table_fill(FILE *input, table_item *table)
{
	uint8_t *buffer = (uint8_t *) malloc(BUFFER_SIZE * sizeof(uint8_t));
	uint32_t total = 0;

	while (true)
	{
		uint32_t amount_of_symbols = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, input);
		total += amount_of_symbols;
		
		for (uint32_t i = 0; i < amount_of_symbols; i++)
		{
			table[buffer[i]].sym = buffer[i];
			table[buffer[i]].count++;
		}

		if (amount_of_symbols < BUFFER_SIZE)
			break;
	}

	free(buffer);

	return total;
}

tree_node *haff_tree_make(priority_queue *queue)
{
	int32_t len = queue_length(queue);

	while (len > 1)
	{
		tree_node *node1 = pop(queue);
		tree_node *node2 = pop(queue);
		tree_node *new_node = unite(node1, node2);

		push(queue, new_node, new_node->count);
		len--;
	}

	return pop(queue);
}

haff_table *haff_table_create()
{
	haff_table *table = (haff_table *)calloc(BUFFER_SIZE, sizeof(haff_table));

	return table;
}

void haff_table_fill(tree_node *root, uint8_t code[BUFFER_SIZE], int32_t *idx, haff_table *table)
{

	if (root == NULL)
		return;

	if (root->left != NULL || root->right != NULL)
	{
		code[(*idx)++] = '0';
		haff_table_fill(root->left, code, idx, table);
	}

	*idx -= (root->left != NULL || root->right != NULL);

	if (root->left == NULL && root->right == NULL)
	{
		table[root->sym].len = *idx;
		memcpy(table[root->sym].code, code, *idx);
	}

	if (root->left != NULL || root->right != NULL)
	{
		code[(*idx)++] = '1';
		haff_table_fill(root->right, code, idx, table);
		*idx -= 1;
	}
}

void bit_write(FILE *output, bit_context *context, uint8_t bit)
{
	if (context->pos == 8)
	{
		fwrite(&(context->buffer), sizeof(uint8_t), 1, output);
		context->pos = 0;
		context->buffer = 0;
	}

	if (bit)
		context->buffer |= (bit << (7 - context->pos));

	context->pos++;
}

void bit_context_flush(FILE *output, bit_context *context)
{
	fwrite(&(context->buffer), sizeof(uint8_t), 1, output);
	context->pos = 0;
	context->buffer = 0;
}

void byte_write(FILE *output, bit_context *context, uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
		bit_write(output, context, (byte >> (7 - i)) & 1);
}

void haff_code_write(haff_table item, bit_context *context, FILE *output)
{
	for (int32_t i = 0; i < item.len; i++)
		bit_write(output, context, (item.code[i] == '1'));
}

void encode_haff_tree(tree_node *root, bit_context *context, FILE *output)
{

	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL)
	{
		bit_write(output, context, 1);
		byte_write(output, context, root->sym);
	}
	else
	{
		bit_write(output, context, 0);
		encode_haff_tree(root->left, context, output);
		encode_haff_tree(root->right, context, output);
	}
}

void encode_count_symbols(FILE *output, tree_node *root, uint32_t amount_of_symbols, bit_context *context)
{
	for (uint8_t i = 0; i < 32; i++)
		bit_write(output, context, (uint8_t)((amount_of_symbols >> (31 - i)) & 1));

	encode_haff_tree(root, context, output);
}

void encode_data(FILE *input, FILE *output, bit_context *context, haff_table *table)
{
	fseek(input, 0, SEEK_SET);
	fseek(input, 1, SEEK_CUR);
	uint8_t *buffer = (uint8_t *)malloc(BUFFER_SIZE * sizeof(uint8_t));

	while (true)
	{
		uint32_t amount_of_symbols = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, input);
		
		for (uint32_t i = 0; i < amount_of_symbols; i++)
			haff_code_write(table[buffer[i]], context, output);

		if (amount_of_symbols < BUFFER_SIZE)
			break;
	}

	bit_context_flush(output, context);
	free(buffer);
}

uint8_t bit_read(bit_context *ctx, FILE *input)
{
	if (ctx->pos == 0 && fread(&(ctx->buffer), sizeof(uint8_t), 1, input) == 0)
		return 2;

	uint8_t bit = (ctx->buffer >> (7 - ctx->pos)) & 1;
	ctx->pos++;

	if (ctx->pos == 8)
		ctx->pos = 0;

	return bit;
}

uint8_t byte_read(bit_context *ctx, FILE *input)
{
	uint8_t byte = 0;

	for (uint8_t i = 0; i < 8; i++)
		byte |= (bit_read(ctx, input) << (7 - i));

	return byte;
}

uint32_t read_count_symbols(FILE *input, bit_context *ctx)
{
	uint32_t alphabet = 0;
	for (uint8_t i = 0; i < 32; i++)
		alphabet |= (((uint32_t)bit_read(ctx, input)) << (31 - i));

	return alphabet;
}

tree_node *tree_read(bit_context *ctx, FILE *input)
{
	tree_node *node = (tree_node *)calloc(1, sizeof(tree_node));
	
	if (bit_read(ctx, input) == 0)
	{
		node->left = tree_read(ctx, input);
		node->right = tree_read(ctx, input);
	}
	else
		node->sym = byte_read(ctx, input);

	return node;
}

uint8_t get_symbol(FILE *input, bit_context *ctx, tree_node *root)
{

	if (root->left == NULL && root->right == NULL)
		return root->sym;

	return (bit_read(ctx, input) == 0 ? get_symbol(input, ctx, root->left) : get_symbol(input, ctx, root->right));
}

void decode_data(FILE *input, FILE *output, bit_context *ctx, tree_node *root, uint32_t amount_of_symbols)
{
	for (int32_t i = 0; i < (int32_t)amount_of_symbols; i++)
	{
		uint8_t sym = get_symbol(input, ctx, root);
		fwrite(&sym, sizeof(uint8_t), 1, output);
	}
}
