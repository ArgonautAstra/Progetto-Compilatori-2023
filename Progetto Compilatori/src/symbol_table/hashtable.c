#include "hashtable.h"

Group *hashtable_group[HASHSIZE] = {0};
Room* linkedlist = NULL;

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
    unsigned int key = hash(group->code_group);
    group->next = hashtable_group[key];
    hashtable_group[key] = group;
}

Group *lookup_group(char *code_group)
{
    Group *group_tmp = hashtable_group[hash(code_group)];
    while (group_tmp != NULL){
        if (strcmp(group_tmp->code_group, code_group) == 0)
            return group_tmp;
        group_tmp = group_tmp->next;
    }
    return NULL;
}

/* LinkedList Room*/

void insert_room(Room* room)
{
    Room * curlist = linkedlist;
    Room * prelist = NULL;
    Room * newlist = room;
    while(curlist != NULL && strcmp(newlist->name,curlist->name) == 1){
        prelist = curlist;
        curlist = curlist->next;
    }
    if(prelist == NULL){
        newlist->next = linkedlist;
        linkedlist = newlist;
    } else {
        prelist->next = newlist;
        newlist->next = curlist;
    }

}

Room* search_room(char *name)
{
    Room* tmp = linkedlist;
    while(tmp != NULL){
        if(strcmp(tmp->name,name) == 0) 
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

/* Print functions*/

float cost_calculator(Booked* rooms, int period)
{
    float totalcost = 0.0;
    for (int i = 0; i < SIZE; i++){
        if(rooms[i].name == NULL) 
            continue;

        Room* room = search_room(rooms[i].name);

        if (room == NULL) 
            yySerror("Check rooms on input file!");
            
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
    for (int i = 0; i < HASHSIZE; i++){
        Group *group = hashtable_group[i];

        if (group == NULL) 
            continue;

        float total = cost_calculator(group->nextroom, group->period);
        fflush(stdout);
        float total_discount = cost_calculator_discount(total, group->members);

        fprintf(yyout, "%s - %s - %d Giorni\n", group->name_group, group->code_group, group->period);
        fprintf(yyout, "Spesa totale del gruppo senza sconto: %.2f\n", total);

        if (total != total_discount)
            fprintf(yyout, "Spesa totale del gruppo con sconto: %.2f\n", total_discount);
        total_hotel += total_discount;

        free(group->nextroom);
        free(group);

        fprintf(yyout, "\n----------\n\n");
    }
    fprintf(yyout, "Spesa totale del albergo: %.2f\n", total_hotel);

    while(linkedlist != NULL){
        Room* room = linkedlist;
        free(room);
        linkedlist = linkedlist->next;
    }
    fflush(yyout);
}

void yySerror(const char *s){
    printf("\nSemantic Error on line: %.2d -> Error: %s.",yylineno,s);
    fclose(yyin);
    fclose(yyout);
    exit(-1);
}
