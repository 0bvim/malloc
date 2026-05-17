/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:55:26 by vde-frei          #+#    #+#             */
/*   Updated: 2026/05/16 22:22:29 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void* default_allocation();

void* malloc(size_t size)
{
    t_alloc* alloc;

    // TODO: add function to align size to 16 bytes, to avoid fragmentation and make it more efficient.
    // TODO: if size is zero, alloc 1 byte and return to reply original malloc behaviour.
    if (size == 0)
        return NULL;
    return default_allocation();
}

static void* default_allocation()
{
    return mmap(NULL, GET_DEFAULT_PAGE_SIZE(), DEFAULT_PROT, DEFAULT_FLAGS, FD_IGN, OFFSET_IGN);
}

