/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:35:53 by igilani           #+#    #+#             */
/*   Updated: 2025/08/25 18:40:30 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"
#include <stdio.h>
#include <string.h>

// Funzione per stampare una struttura json
void print_json(json *j, int indent);

// Funzione per stampare una mappa JSON
void print_map(json *j, int indent) {
    printf("{\n");
    for (size_t i = 0; i < j->map.size; i++) {
        for (int k = 0; k < indent + 2; k++) printf(" ");
        printf("\"%s\": ", j->map.data[i].key);
        print_json(&j->map.data[i].value, indent + 2);
        if (i < j->map.size - 1)
            printf(",");
        printf("\n");
    }
    for (int k = 0; k < indent; k++) printf(" ");
    printf("}");
}

// Funzione per stampare una struttura json
void print_json(json *j, int indent) {
    switch (j->type) {
        case MAP:
            print_map(j, indent);
            break;
        case INTEGER:
            printf("%d", j->integer);
            break;
        case STRING:
            printf("\"%s\"", j->string);
            break;
    }
}

// Funzione per liberare una struttura json
void free_json(json *j) {
    if (j->type == MAP) {
        for (size_t i = 0; i < j->map.size; i++) {
            free(j->map.data[i].key);
            free_json(&j->map.data[i].value);
        }
        free(j->map.data);
    } else if (j->type == STRING) {
        free(j->string);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file;
    if (strcmp(argv[1], "/dev/stdin") == 0) {
        file = stdin;
    } else {
        file = fopen(argv[1], "r");
        if (!file) {
            perror("Failed to open file");
            return 1;
        }
    }

    json j;
    int result = argo(&j, file);

    if (result == 1) {
        print_json(&j, 0);
        printf("\n");
        free_json(&j);
    } else {
        printf("Parsing failed\n");
    }

    if (file != stdin)
        fclose(file);

    return result == 1 ? 0 : 1;
}

