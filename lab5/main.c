#include "./huffman_codes/huffman_codes.h"

int32_t compare(const void *a, const void *b)
{
	return ((const table_item *)a)->count - ((const table_item *)b)->count;
}

void encode(FILE *input, FILE *output)
{
	table_item *hash_table = table_make();
	uint32_t amount_of_symbols = table_fill(input, hash_table);

	if (amount_of_symbols == 0)
	{
		cleanup(input, output, NULL, hash_table, NULL, NULL);
		return;
	}

	qsort(hash_table, BUFFER_SIZE, sizeof(table_item), compare);

	priority_queue *queue = pr_queue_make();
	queue_fill(queue, hash_table);

	tree_node *root = haff_tree_make(queue);

	haff_table *haff_table = haff_table_create();

	int32_t idx = 0;
	uint8_t code[BUFFER_SIZE] = {0};

	haff_table_fill(root, code, &idx, haff_table);

	bit_context context = {0};

	encode_count_symbols(output, root, amount_of_symbols, &context);

	encode_data(input, output, &context, haff_table);

	cleanup(input, output, queue, hash_table, root, haff_table);

}

void decode(FILE *input, FILE *output)
{
	bit_context context = {0};

	uint32_t total = read_count_symbols(input, &context);
	if (total == 0)
	{
		cleanup(input, output, NULL, NULL, NULL, NULL);
		return;
	}

	tree_node *haff_tree = tree_read(&context, input);

	decode_data(input, output, &context, haff_tree, total);

	cleanup(input, output, NULL, NULL, haff_tree, NULL);
}

int main()
{
	FILE *input = NULL;
	FILE *output = NULL;

	if ((input = fopen("in.txt", "rb")) == NULL)
		return 0;

	if ((output = fopen("out.txt", "wb")) == NULL)
	{
		fclose(input);
		return 0;
	}

	char to_do;

	if (fscanf(input, "%c", &to_do) < 1)
	{
		fclose(input);
		fclose(output);
		return 0;
	}

	if (to_do == 'c')
		encode(input, output);
	else
		decode(input, output);

	return 0;
}
