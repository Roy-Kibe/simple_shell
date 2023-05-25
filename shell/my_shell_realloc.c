#include "shell.h"

/**
 **set_memory - fills memory with a constant byte
 *@mem: the pointer to the memory area
 *@a: the byte to fill *s with
 *@k: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *set_memory(char *mem, char a, unsigned int k)
{
	unsigned int j;

	for (j = 0; j < k; j++)
		mem[j] = a;
	return (mem);
}

/**
 * free_string_set - frees a string of strings
 * @ss: string of strings
 */
void free_string_set(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}

/**
 * realloc_mem - reallocates a block of memory
 * @mem_ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @curr_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc_mem(void *mem_ptr, unsigned int prev_size,
		unsigned int curr_size)
{
	char *ph;

	if (!mem_ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(mem_ptr), NULL);
	if (curr_size == prev_size)
		return (mem_ptr);

	ph = malloc(curr_size);
	if (!ph)
		return (NULL);

	prev_size = prev_size < curr_size ? prev_size : curr_size;
	while (prev_size--)
		ph[prev_size] = ((char *)mem_ptr)[prev_size];
	free(mem_ptr);
	return (ph);
}
