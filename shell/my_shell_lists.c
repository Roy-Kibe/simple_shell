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
	list_t *nw_hd;

	if (!hd_node)
		return (NULL);
	nw_hd = malloc(sizeof(list_t));
	if (!nw_hd)
		return (NULL);
	set_memory((void *)nw_hd, 0, sizeof(list_t));
	nw_hd->num = index;
	if (strn)
	{
		nw_hd->str = str_clone(strn);
		if (!nw_hd->str)
		{
			free(nw_hd);
			return (NULL);
		}
	}
	nw_hd->next = *hd_node;
	*hd_node = nw_hd;
	return (nw_hd);
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
	list_t *nw_nd, *nd;

	if (!hd_node)
		return (NULL);

	nd = *hd_node;
	nw_nd = malloc(sizeof(list_t));
	if (!nw_nd)
		return (NULL);
	set_memory((void *)nw_nd, 0, sizeof(list_t));
	nw_nd->num = index;
	if (strn)
	{
		nw_nd->str = str_clone(strn);
		if (!nw_nd->str)
		{
			free(nw_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = nw_nd;
	}
	else
		*hd_node = nw_nd;
	return (nw_nd);
}

/**
 * DisplayStrList - prints only the str element of a list_t linked list
 * @ptr_h: pointer to first node
 *
 * Return: size of list
 */
size_t DisplayStrList(const list_t *ptr_h)
{
	size_t a = 0;

	while (ptr_h)
	{
		_puts(ptr_h->str ? ptr_h->str : "(nil)");
		_puts("\n");
		ptr_h = ptr_h->next;
		a++;
	}
	return (a);
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
	list_t *nd, *pv_nd;
	unsigned int a = 0;

	if (!hd_node || !*hd_node)
		return (0);

	if (!nd_index)
	{
		nd = *hd_node;
		*hd_node = (*hd_node)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *hd_node;
	while (nd)
	{
		if (a == nd_index)
		{
			pv_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		a++;
		pv_nd = nd;
		nd = nd->next;
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
	list_t *nd, *nt_nd, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	nd = hd;
	while (nd)
	{
		nt_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = nt_nd;
	}
	*hd_ptr = NULL;
}
