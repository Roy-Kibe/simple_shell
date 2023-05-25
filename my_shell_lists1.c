#include "shell.h"

/**
 * list_size - determines length of linked list
 * @hd_node: pointer to first node
 *
 * Return: size of list
 */
size_t list_size(const list_t *hd_node)
{
	size_t j = 0;

	while (hd_node)
	{
		hd_node = hd_node->next;
		j++;
	}
	return (j);
}

/**
 * list_to_text - returns an array of strings of the list->str
 * @head_ptr: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_text(list_t *head_ptr)
{
	list_t *node = head_ptr;
	size_t i = list_size(head_ptr), j;
	char **strns;
	char *s;

	if (!head_ptr || !i)
		return (NULL);
	strns = malloc(sizeof(char *) * (i + 1));
	if (!strns)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(strlen(node->str) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(strns[j]);
			free(strns);
			return (NULL);
		}

		s = cpy_str(s, node->str);
		strns[i] = s;
	}
	strns[i] = NULL;
	return (strns);
}


/**
 * display_list - prints all elements of a list_t linked list
 * @hd_node: pointer to first node
 *
 * Return: size of list
 */
size_t display_list(const list_t *hd_node)
{
	size_t j = 0;

	while (hd_node)
	{
		_puts(convertNum(hd_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd_node->str ? hd_node->str : "(nil)");
		_puts("\n");
		hd_node = hd_node->next;
		j++;
	}
	return (j);
}

/**
 * node_begins_with - returns node whose string starts with prefix
 * @ls_node: pointer to list head
 * @prefix_str: string to match
 * @a: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_begins_with(list_t *ls_node, char *prefix_str, char a)
{
	char *ptr = NULL;

	while (ls_node)
	{
		ptr = begins_with(ls_node->str, prefix_str);
		if (ptr && ((a == -1) || (*ptr == a)))
			return (ls_node);
		ls_node = ls_node->next;
	}
	return (NULL);
}

/**
 * locate_node_index - gets the index of a node
 * @head_ptr: pointer to list head
 * @node_ptr: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t locate_node_index(list_t *head_ptr, list_t *node_ptr)
{
	size_t j = 0;

	while (head_ptr)
	{
		if (head_ptr == node_ptr)
			return (j);
		head_ptr = head_ptr->next;
		j++;
	}
	return (-1);
}
