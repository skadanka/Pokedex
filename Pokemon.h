/*
 * Pokedex.h
 *
 *  Created on: Nov 16, 2021
 *      Author: ise
 */
#include "Defs.h"

#ifndef POKEMON_H_
#define POKEMON_H_

typedef enum {PokemonFound, PokemonNotFound, NoPokemonType} PokemonResult;
typedef enum {me, other} pick_side;
typedef enum {rm, add} operation;

typedef struct Biological_info{
	int attack;
	float weight;
	float height;
}B_Info;

typedef struct Type_t Type;

typedef struct Pokemon_t{
	char *name;
	Type *type;
	char *specie;
	B_Info *Bio_Info;
}Pokemon;

struct Type_t{
	char* name;
	int num_of_pokemons;
	Pokemon** pokemons;
	Type** effective_me;
	Type** effective_other;
};

typedef struct Pokedex_t{
	int num_of_pokemons;
	int num_of_types;
	Pokemon** pokemons;
	Type** types;
}Pokedex;

// Main Loading function
Pokedex* create_Pokedex(char** data, int num_of_pokemons, int num_of_types, int pokemonStart, int num_of_Lines );

// The main Unloading methods
// Here we Unloading Our Pokedex
//		all The data stored in char** dynamic array for each Line
//		All the info in our Pokedex use those lines directly, so we Free Each line From static global Data
//		and all our fields across the structs will be freed
//		lastly we free the Pokemons, // unload_Pokemons: freeall Pokedex->pokemons[i] and then the Pokemons alocated array
//		Type Structs and all the fields allocted there// unload_types freeall Pokedex->types[i] and then free the pokedex->types
//
void unload_Pokedex(Pokedex *pokedex);

// search Type
// Search type based on given string in the Pokedex in return the pokedex->types[i]->name = type Integer
int search_type(char* type, Pokedex *pokedex);
Pokemon* createPokemonInsert(char* pokemon, Pokedex* pokedex);

int equalPokemonsAttack(element poke1, element poke2);
element copyPokemon(element poke);
char* getType(element poke);
int getPokemonsAttack(element firstElem, element secondElem, int* attackFirst,int* attackSecond);
status freePokemon(element Elem);
// print Functions
// Get the entire Pokedex
// 		iterating over the num of types and for each Type will print it with print_type function
//		print type function written in the c Code and declared there because our user never acsses to print type on its own
//		Used for Case 2 in MainFirst
void print_all_types(Pokedex *pokedex);

void unload_Pokemons(Pokemon** pokemons, int num_of_pokemons);
// Print all Pokemons
//		iterate over num_of_pokemons and use the function Print_Pokemon for each Pokemon
//		print nothing if num_of_pokemons is 0
//		Used for Case 1 in the Main First
void print_all_Pokemons(Pokedex* pokedex);

// Print_Pokemon Template example:
////	Pikachu :
//		MousePokemon, Electric Type.
//		Height: 0.40 m Weight: 6.00 kg Attack: 55
//		The stats printed By void print_Bio_Info(B_Info *Bio_Info) The user never need direct accsses to this field
//		Used for Case 7, for the found Pokemon
status printPokemon(element elem);
void print_Pokemon(Pokemon *pokemon);

B_Info* createBio(int attack, float weight, float height);
int search_effect_str(Type** effects, char* eff);

// Print all By Type
//		With given template. And iterate over Type->Pokemons[i] and Print each Pokemon in given list
//		Case 8
void print_pokemons_by_type(Pokedex* pokedex, int index);
void print_type(Type* ptype);
// By given Pokemon name we will search in the pokedex->Pokemons array and by index passed by reference we will
// index = i, if the pokemon found at pokedex->pokemons[i] place
// Status used to check if the precocious failed or succeeded
status search_Pokemon(char* pokemon_str, int* index, Pokedex* pokedex);
Pokemon* create_pokemon(char* name, char* specie, char* height_str, char* weight_str, char* attack_str);
Type** remove_effect(int type_index, Type** effects);
Type** add_effect(Type* type, Type** effects);
// By Given index found with search_type method for typeB and typeA In case both exist
// we will use the indexex to remove\add the wanted type from type effective_[me, other] lists
// Using pick_side {me, 0ther} for cases to determine from which list we remove/add
// using opertion{add, rm} to determine the action used From the mainFirst cases
// passing the pokedex by reference beacuse updates will be made
status  typeA_effect_typeB(int typeA, int typeB, pick_side effect_side, operation effect_operation, Pokedex *pokedex);
#endif /* DEFS_H_ */
