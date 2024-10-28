#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

enum { BUFFER_SIZE = 256 };

typedef struct item
{
	uint8_t sym;
	uint32_t count;
} table_item;

typedef struct tree_node
{
	uint8_t sym;
	uint32_t count;
	struct tree_node *left;
	struct tree_node *right;
} tree_node;

typedef struct priority_queue_item
{
	tree_node *node;
	uint32_t priority;
	struct priority_queue_item *next;
} priority_queue_item;

typedef struct priority_queue
{
	priority_queue_item *head;
} priority_queue;

priority_queue *pr_queue_make();

void push(priority_queue *queue, tree_node *node, uint32_t priority);

tree_node *pop(priority_queue *queue);

void pr_queue_destroy(priority_queue *queue);

int32_t queue_length(priority_queue *queue);

tree_node *node_make(table_item item);

void queue_fill(priority_queue *queue, table_item *hash_table);

void tree_destroy(tree_node *root);

tree_node *unite(tree_node *node1, tree_node *node2);
