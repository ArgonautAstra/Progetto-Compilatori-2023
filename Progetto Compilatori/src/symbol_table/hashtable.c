#include "hashtable.h"

Room *hashtable_room[HASHSIZE] = {0};
Group *hashtable_group[HASHSIZE] = {0};

/* Auxiliary Functions*/

Group *create_group(char *name_group, char *code_group, int members, int period, Booked* rooms)
{
    Group *group = malloc(sizeof(Group));
    group->name_group = strdup(name_group);
    group->code_group = strdup(code_group);
    group->members = members;
    group->nextroom = rooms;
    group->period = period;
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

void create_booked(Booked* room,char *name, int booked)
{
    room->name = strdup(name);
    room->booked = booked;
}

/* Hash function*/

unsigned int hash(char *s)
{
    int h = 0;
    for (; *s != '\0'; s++)
        h = (127 * h + *s) % HASHSIZE;
    return h;
}

/* HASHTABLE  (int,Group) */

void insert_group(Group *group)
{
    if (lookup_group(group->code_group) != NULL)
        return;
    // printf("Group: %s,%s\n", group->name_group,group->code_group);
    unsigned int key = hash(group->code_group);
    group->next = hashtable_group[key];
    hashtable_group[key] = group;
}

Group *lookup_group(char *code_group)
{
    Group *group_tmp = hashtable_group[hash(code_group)];
    while (group_tmp != NULL)
    {
        if (strcmp(group_tmp->code_group, code_group) == 0)
            return group_tmp;
        group_tmp = group_tmp->next;
    }
    return NULL;
}

/* HASHTABLE (int,Room)*/

void insert_room(Room *room)
{
    if (lookup_room(room->name) != NULL)
        return;
    unsigned int key = hash(room->name);
    room->next = hashtable_room[key];
    hashtable_room[key] = room;
}

Room* lookup_room(char *name)
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

/* Print functions*/

float cost_calculator(Booked* rooms, int period)
{
    float totalcost = 0.0;
    for (int i = 0; i < SIZE; i++){
        if(rooms[i].name == NULL) continue;
        Room* room = lookup_room(rooms[i].name);
        if (room == NULL)
            continue;
        totalcost += room->cost * rooms[i].booked;
    }
    totalcost *= period;
    return totalcost;
}

float cost_calculator_discount(float total, int members)
{
    if (members >= 30 && members < 50)
        total -= (total * 15) / 100;
    else if (members >= 50)
        total -= (total * 25) / 100;
    return total;
}

void print_tot()
{
    float total_hotel = 0.0;
    for (int i = 0; i < HASHSIZE; i++)
    {
        Group *group = hashtable_group[i];
        if (group == NULL) continue;
        float total = cost_calculator(group->nextroom, group->period);
        fflush(stdout);
        float total_discount = cost_calculator_discount(total, group->members);
        fprintf(yyout, "%s - %s - %d Giorni\n", group->name_group, group->code_group, group->period);
        fprintf(yyout, "Spesa totale del gruppo senza sconto: %.2f\n", total);

        if (total != total_discount)
            fprintf(yyout, "Spesa totale del gruppo con sconto: %.2f\n", total_discount);
        total_hotel += total_discount;

        fprintf(yyout, "\n----------\n\n");
        
    }
    fprintf(yyout, "Spesa totale del albergo: %.2f\n\n", total_hotel);
    fflush(yyout);
}