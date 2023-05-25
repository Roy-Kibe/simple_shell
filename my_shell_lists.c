#include "shell.h"

/**
 * addNewNode - adds a node to the start of the list
 * @hd_node: address of pointer to head node
 * @strn: str field of node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *addNewNode(list_t **hd_node, const char *strn, int index)
{
	list_t *new_hd;

	if (!hd_node)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	set_memory((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = index;
	if (strn)
	{
		new_hd->str = str_clone(strn);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd_node;
	*hd_node = new_hd;
	return (new_hd);
}

/**
 * appendNode - adds a node to the end of the list
 * @hd_node: address of pointer to head node
 * @strn: str field of node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *appendNode(list_t **hd_node, const char *strn, int index)
{
	list_t *newNode, *alias_node;

	if (!hd_node)
		return (NULL);

	alias_node = *hd_node;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	set_memory((void *)newNode, 0, sizeof(list_t));
	newNode->num = index;
	if (strn)
	{
		newNode->str = str_clone(strn);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (alias_node)
	{
		while (alias_node->next)
			alias_node = alias_node->next;
		alias_node->next = newNode;
	}
	else
		*hd_node = newNode;
	return (newNode);
}

/**
 * DisplayStrList - prints only the str element of a list_t linked list
 * @ptr_h: pointer to first node
 *
 * Return: size of list
 */
size_t DisplayStrList(const list_t *ptr_h)
{
	size_t j = 0;

	while (ptr_h)
	{
		_puts(ptr_h->str ? ptr_h->str : "(nil)");
		_puts("\n");
		ptr_h = ptr_h->next;
		j++;
	}
	return (j);
}

/**
 * remove_node_at_index - deletes node at given index
 * @hd_node: address of pointer to first node
 * @nd_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **hd_node, unsigned int nd_index)
{
	list_t *d_node, *last_node;
	unsigned int j = 0;

	if (!hd_node || !*hd_node)
		return (0);

	if (!nd_index)
	{
		d_node = *hd_node;
		*hd_node = (*hd_node)->next;
		free(d_node->str);
		free(d_node);
		return (1);
	}
	d_node = *hd_node;
	while (d_node)
	{
		if (j == nd_index)
		{
			last_node->next = d_node->next;
			free(d_node->str);
			free(d_node);
			return (1);
		}
		j++;
		last_node = d_node;
		d_node = d_node->next;
	}
	return (0);
}

/**
 * clear_list - frees all nodes of a list
 * @hd_ptr: address of pointer to head node
 *
 * Return: void
 */
void clear_list(list_t **hd_ptr)
{
	list_t *node, *nextNode, *hd_node;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd_node = *hd_ptr;
	node = hd_node;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	*hd_ptr = NULL;
}
