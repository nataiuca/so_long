/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:33:50 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 20:05:28 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>

t_queue *create_queue(int capacity) {
    t_queue *queue = (t_queue *)malloc(sizeof(t_queue));
    queue->x = (int *)malloc(sizeof(int) * capacity);
    queue->y = (int *)malloc(sizeof(int) * capacity);
    queue->front = queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Función para verificar si la cola está vacía
bool is_queue_empty(t_queue *queue) {
    return queue->front == -1;
}

// Función para encolar un elemento
void enqueue(t_queue *queue, int x, int y) {
    if (queue->rear == queue->capacity - 1) return;
    if (queue->front == -1) queue->front = 0;
    queue->rear++;
    queue->x[queue->rear] = x;
    queue->y[queue->rear] = y;
}

// Función para desencolar un elemento
void dequeue(t_queue *queue, int *x, int *y) {
    if (is_queue_empty(queue)) return;
    *x = queue->x[queue->front];
    *y = queue->y[queue->front];
    if (queue->front == queue->rear) queue->front = queue->rear = -1;
    else queue->front++;
}

// Función para liberar la memoria de la cola
void free_queue(t_queue *queue) {
    free(queue->x);
    free(queue->y);
    free(queue);
}
