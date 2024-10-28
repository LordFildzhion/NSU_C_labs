#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "../queue/queue.h"

typedef struct haff_table
{
	uint8_t code[BUFFER_SIZE];
	int32_t len;
} haff_table;

typedef struct bit_contex
{
	uint8_t buffer;
	int32_t pos;
} bit_context;

table_item *table_make();

void cleanup(FILE *input, FILE *output, priority_queue *queue, table_item *table, tree_node *root, haff_table *h_table);

uint32_t table_fill(FILE *input, table_item *table);

tree_node *haff_tree_make(priority_queue *queue);

haff_table *haff_table_create();

void haff_table_fill(tree_node *root, uint8_t code[BUFFER_SIZE], int32_t *idx, haff_table *table);

void bit_write(FILE *output, bit_context *context, uint8_t bit);

void bit_context_flush(FILE *output, bit_context *context);

void byte_write(FILE *output, bit_context *context, uint8_t byte);

void haff_code_write(haff_table item, bit_context *context, FILE *output);

void encode_haff_tree(tree_node *root, bit_context *context, FILE *output);

void encode_count_symbols(FILE *output, tree_node *root, uint32_t amount_of_symbols, bit_context *context);

void encode_data(FILE *input, FILE *output, bit_context *context, haff_table *table);

uint8_t bit_read(bit_context *ctx, FILE *input);

uint8_t byte_read(bit_context *ctx, FILE *input);

uint32_t read_count_symbols(FILE *input, bit_context *ctx);

tree_node *tree_read(bit_context *ctx, FILE *input);

uint8_t get_symbol(FILE *input, bit_context *ctx, tree_node *root);

void decode_data(FILE *input, FILE *output, bit_context *ctx, tree_node *root, uint32_t amount_of_symbols);
