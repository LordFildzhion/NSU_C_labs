#include "./queue.h"

priority_queue *pr_queue_make()
{
	priority_queue *queue = (priority_queue *) calloc(1, sizeof(priority_queue));
	return queue;
}

void push(priority_queue *queue, tree_node *node, uint32_t priority)
{
	priority_queue_item *item = (priority_queue_item *) malloc(sizeof(priority_queue_item));
	
	item->priority = priority;
	item->node = node;

	if (queue->head == NULL)
	{
		item->next = NULL;
		queue->head = item;
	}
	else
	{
		priority_queue_item *current = queue->head;
		priority_queue_item *last = NULL;
		while (true)
		{
			if (current->priority > priority)
			{
				if (last == NULL)
				{
					item->next = current;
					queue->head = item;
				}
				else
				{
					item->next = current;
					last->next = item;
				}
				break;
			}
			else
			{
				last = current;
				current = last->next;

				if (current == NULL)
				{
					item->next = NULL;
					last->next = item;
					break;
				}
			}
		}
	}
}

tree_node *pop(priority_queue *queue)
{
	priority_queue_item *item = queue->head;

	queue->head = item->next;
	tree_node *node = item->node;

	free(item);

	return node;
}

void pr_queue_destroy(priority_queue *queue)
{
	free(queue);
}

int32_t queue_length(priority_queue *queue)
{

	priority_queue_item *item = queue->head;

	if (item == NULL)
		return 0;

	int32_t len = 1;
	while (item->next != NULL)
	{
		len++;
		item = item->next;
	}

	return len;
}

tree_node *node_make(table_item item)
{
	tree_node *node = (tree_node *) calloc(1, sizeof(tree_node));

	node->count = item.count;
	node->sym = item.sym;

	return node;
}

void queue_fill(priority_queue *queue, table_item *hash_table)
{
	for (uint32_t i = 0; i < BUFFER_SIZE; i++)
	{
		if (hash_table[i].count != 0)
		{
			tree_node *node = node_make(hash_table[i]);
			push(queue, node, hash_table[i].count);
		}
	}
}

void tree_destroy(tree_node *root)
{

	if (root == NULL)
		return;

	tree_destroy(root->left);
	tree_destroy(root->right);

	free(root);
}

tree_node *unite(tree_node *node1, tree_node *node2)
{
	tree_node *new_node = (tree_node *) calloc(1, sizeof(tree_node));
	
	new_node->count = node1->count + node2->count;

	new_node->left = node1;
	new_node->right = node2;

	return new_node;
}
