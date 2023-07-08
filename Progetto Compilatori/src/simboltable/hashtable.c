#include "hashtable.h"
/**
 * "Pippobaudo" - 6666/GT - Periodo
 * Spesa totale del gruppo senza sconto: %lf
 * Spesa totale del gruppo con sconto: %lf
 *
 *
 *
 *
 *
 * Spesa totale dell'albergo: %lf
 */
/**
 * Nome gruppo - codice gruppo - membri totale del gruppo - Periodo
 *
 * Nome delle camera - prezzo delle camera
 *
 *
 * mese/anno
 *
 */

Group *create_group(char *name_group, char *code_group, int members, char *period, Booked *rooms)
{
    Group *group = malloc(sizeof(Group));
    group->name_group = strdup(name_group);
    group->code_group = strdup(code_group);
    group->members = members;
    group->period = strdup(period);
    group->nextroom = rooms; // Linked list of booked rooms
    group->next = NULL;
    return group;
}

Room *create_room(char *name, float cost)
{
    Room *room = malloc(sizeof(Room));
    room->name = strdup(name);
    room->cost = cost;
    room->next = NULL;
    return room;
}

Booked *create_booked(char *name, int booked)
{
    Booked *room = malloc(sizeof(Booked));
    room->name = strdup(name);
    room->booked = booked;
    room->next = NULL;
    return room;
}

unsigned int hash(char *s)
{
    int h = 0, a = 127;
    for (; *s != '\0'; s++)
        h = (a * h + *s) % HASHSIZE;
    return h;
}

void insert_group(Group *group)
{
    if (lookup_group(group->name_group) != NULL)
        return;
    unsigned int key = hash(group->name_group);
    group->next = hashtable_group[key];
    hashtable_group[key] = group;
}

Group *lookup_group(char *name_group)
{
    Group *group_tmp = hashtable_group[hash(name_group)];
    while (group_tmp != NULL)
    {
        if (strcmp(group_tmp->name_group, name_group) == 0)
            return group_tmp;
        group_tmp = group_tmp->next;
    }
    return NULL;
}

void insert_room(Room *room)
{
    if (lookup_group(room->name) != NULL)
        return;
    unsigned int key = hash(room->name);
    room->next = hashtable_group[key];
    hashtable_group[key] = room;
}

Room *lookup_room(char *name)
{
    Room *room_tmp = hashtable_room[hash(name)];
    while (room_tmp != NULL)
    {
        if (strcmp(room_tmp->name, name) == 0)
            return room_tmp;
        room_tmp = room_tmp->next;
    }
    return NULL;
}

void insert_booked(Booked** booked_list, Booked *booked)
{
    Booked *curlist = *booked_list;
    Booked *prelist = NULL;
    Booked *newlist = booked;
    while (curlist != NULL)
    {
        prelist = curlist;
        curlist = curlist->next;
    }

    if (prelist == NULL)
    {
        newlist->next = booked_list;
        *booked_list = newlist;
    }
    else
    {
        prelist->next = newlist;
        newlist->next = curlist;
    }
}

void stampalista(Booked *node)
{
    if (node == NULL)
        printf("Lista vuota!\n");
    else
    {
        while (node != NULL)
        {
            printf("name:%s, booked:%f\n", node->name, node->booked);
            node = node->next;
        }
    }
}

float cost_calculator(Booked *rooms)
{
    float totalcost = 0.0;
    while (rooms != NULL)
    {
        Room *room = lookup_room(rooms->name);
        if (room == NULL)
            continue;
        totalcost += room->cost * rooms->booked;
        rooms = rooms->next;
    }
    return totalcost;
}

float cost_calculator_discount(Booked *rooms, int members)
{
    float total = cost_calculator(rooms);
    if (members >= 30 && members < 50)
        total -= (total * 15) / 100;
    else if (members >= 50)
        total -= (total * 25) / 100;
    return total;
}

void print_tot()
{
    float total_hotel;
    for (int i = 0; i < HASHSIZE; i++)
    {
        Group *group = hashtable_group[i];
        if (group != NULL)
        {
            float total = cost_calculator(group->nextroom), total_discount = cost_calculator_discount(group->nextroom, group->members);
            fprintf(yyout, "%s - %s - %s\n", group->name_group, group->code_group, group->period);
            fprintf(yyout, "Spesa totale del gruppo senza sconto: %f\n", total);
            if (total != total_discount)
                fprintf(yyout, "Spesa totale del gruppo con sconto: %f\n", total_discount);
            total_hotel += total_discount;
        }
        fprintf(yyout, "\n\n\n");
    }
    fprintf(yyout, "Spesa totale del albergo: %f", total_hotel);
}
