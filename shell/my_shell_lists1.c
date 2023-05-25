#include "shell.h"

/**
 * list_size - determines length of linked list
 * @hd_node: pointer to first node
 *
 * Return: size of list
 */
size_t list_size(const list_t *hd_node)
{
	size_t a = 0;

	while (hd_node)
	{
		hd_node = hd_node->next;
		a++;
	}
	return (a);
}

/**
 * list_to_text - returns an array of strings of the list->str
 * @head_ptr: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_text(list_t *head_ptr)
{
	list_t *nd = head_ptr;
	size_t a = list_size(head_ptr), b;
	char **strs;
	char *str;

	if (!head_ptr || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; nd; nd = nd->next, a++)
	{
		str = malloc(_strlength(nd->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = cpy_str(str, nd->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * display_list - prints all elements of a list_t linked list
 * @hd_node: pointer to first node
 *
 * Return: size of list
 */
size_t display_list(const list_t *hd_node)
{
	size_t a = 0;

	while (hd_node)
	{
		_puts(convertNum(hd_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd_node->str ? hd_node->str : "(nil)");
		_puts("\n");
		hd_node = hd_node->next;
		a++;
	}
	return (a);
}

/**
 * *node_begins_with - returns node whose string starts with prefix
 * @ls_node: pointer to list head
 * @prefix_str: string to match
 * @a: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_begins_with(list_t *ls_node, char *prefix_str, char a)
{
	char *pt = NULL;

	while (ls_node)
	{
		pt = begins_with(ls_node->str, prefix_str);
		if (pt && ((a == -1) || (*pt == a)))
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
	size_t a = 0;

	while (head_ptr)
	{
		if (head_ptr == node_ptr)
			return (a);
		head_ptr = head_ptr->next;
		a++;
	}
	return (-1);
}
