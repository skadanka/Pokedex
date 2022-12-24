#include "Pokemon.h"
#include "Defs.h"

static char **data;
static int num_of_lines;

// Create The Pokedex __INIT__
status assigen_pokemonTotype(Type* type, Pokemon *pokemon);
void load_effect(char** lines, int end_line, Pokedex* pokedex);

// Create The Pokemons object Array
Pokemon* create_pokemon(char* name, char* specie, char* height, char* weight, char* attack);
void create_Pokemons(char **pokemon_str, int num_of_pokemons, int start, Pokedex *pokedex);

// Create The types object array
void create_types(char *str, int num_of_types, Pokedex* pokedex);

// Print Methods
void print_Bio_Info(B_Info *Bio_Info);
void print_pokemon_list(Pokemon** pokemons, int size);

// Useful Methods
char** slice_str(char* str, char* del);

// UNLOAD METHODS
void unload_Types(Type** types, int num_of_types);

// Header file methods
int search_effect_str(Type** effects, char* eff);
Type** remove_effect(int type_index, Type** effects);
Type** add_effect(Type* type, Type** effects);

Pokedex* create_Pokedex(char** data, int num_of_pokemons, int num_of_types, int pokemonStart, int num_of_Lines )
{

	// create all known size of types, pokemons, effective etc..

	// calculate the max Lines possiable in the configrution file
	num_of_lines = num_of_Lines;
	// Pointer array to each line in the end of scanning under!


	//Init pokedex
	Pokedex* pokedex = (Pokedex*) malloc(sizeof(Pokedex));
	if(pokedex == NULL){
		return NULL;
	}

	// init the fields of the Pokedex
	// num_of_pokemons, num_of_types integer to keep our pokedex size
	// types, pokemons array of pointers for the that types holding all the type, pokemons in our database;
	pokedex->num_of_pokemons = 0;
	pokedex->num_of_types = 0;
	pokedex->pokemons = NULL;
	pokedex->types = NULL;

	if(num_of_types >0){
		create_types(data[1], num_of_types, pokedex);
		load_effect(data, pokemonStart, pokedex);
		create_Pokemons(data, num_of_pokemons, pokemonStart, pokedex);
	}

	return pokedex;
}




void print_Bio_Info(B_Info *Bio_Info){
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d",
			Bio_Info->height, Bio_Info->weight, Bio_Info->attack);
}

void print_Pokemon(Pokemon *pokemon){
	printf("%s :\n", pokemon->name);
	printf("%s, %s Type.\n", pokemon->specie, pokemon->type->name);
	print_Bio_Info(pokemon->Bio_Info);
	printf("\n\n");
}
void print_pokemons_list(Pokemon** pokemons, int size){
	for(int i = 0; i < size; i++)
		print_Pokemon(pokemons[i]);
}
void print_all_Pokemons(Pokedex* pokedex){

	for(int i = 0; i < pokedex->num_of_pokemons; i++)
			print_Pokemon(pokedex->pokemons[i]);
}

void print_pokemons_by_type(Pokedex *pokedex, int index){
	if(pokedex->types[index]->num_of_pokemons == 0)
		printf("There are no Pokemons with this type.\n");
	else{
		printf("There are %d Pokemons with this type:\n", pokedex->types[index]->num_of_pokemons);
		print_pokemons_list(pokedex->types[index]->pokemons, pokedex->types[index]->num_of_pokemons);
	}
}

void print_type(Type* ptype){
	int i;
	printf("Type %s -- %d pokemons\n", ptype->name, ptype->num_of_pokemons);
	if(ptype->effective_me[0] != NULL){
		printf("	These types are super-effective against %s:", ptype->name);

		for(i = 0; ptype->effective_me[i+1] !=NULL; i++)
			printf("%s ,", ptype->effective_me[i]->name);
		printf("%s\n", ptype->effective_me[i]->name);
	}

		if(ptype->effective_other[0] != NULL){
		printf("	%s moves are super-effective against:", ptype->name);
		for(i = 0; ptype->effective_other[i+1] !=NULL; i++)
			printf("%s ,", ptype->effective_other[i]->name);
		printf("%s\n", ptype->effective_other[i]->name);
	}

	printf("\n");
}

// can make it better by send the types directly
void print_all_types(Pokedex *pokedex){
	for(int i = 0; i < pokedex->num_of_types; i++)
		print_type(pokedex->types[i]);

	return;
}

void load_effect(char** lines, int end_line, Pokedex* pokedex){
	int start = 2;
	char** traits, *side, *type;
	char** data1, **data2, **data3;
	char* sides[] = {"me", "other"};
	pick_side choose;
	if(start == end_line)
		return;
	for(int i = start; i < end_line - 1; i++){
		data1 = slice_str(lines[i], ":");
		traits = slice_str(data1[1], ",");
		data2 = slice_str(data1[0], " ");
		type = data2[0];
		data3 = slice_str(data2[1], "-");
		side = data3[2];

		if(strcmp(side, sides[0]) == 0)
			choose = me;
		else
			choose = other;

		for(int t = 0; traits[t] != NULL; t++)
			typeA_effect_typeB(search_type(type, pokedex), search_type(traits[t], pokedex), choose, add, pokedex);

		free(data1);
		free(data2);
		free(data3);
		free(traits);
	}

	return;
}


// Increase Num_of_pokemons in current Type
// realloc the current size of + sizeof(Pokemon*)
// point the added Pokemon* to pokemon argument given by the Pokedex __init__
status assigen_pokemonTotype(Type* type, Pokemon *pokemon){
	type->num_of_pokemons++;
	type->pokemons = (Pokemon**) realloc(type->pokemons, sizeof(Pokemon*)*(type->num_of_pokemons));
	if(type->pokemons == NULL){
		printf("Memory problem\n");
		return failure;
	}
	type->pokemons[type->num_of_pokemons-1] = pokemon;
	pokemon->type = type;
	return success;
}


// return the index of Given char* type in our Database will be used for many reasons
int search_type(char* type, Pokedex *pokedex){
	if(type != NULL){
		for(int i = 0; i < pokedex->num_of_types; i++){
			if(strcmp(type, pokedex->types[i]->name) == 0)
				// printf("given type: %s found: %s \n",type, pokedex->types[i]->name);
				return i;
		}
	}
	return -1;
}

status search_Pokemon(char* pokemon_str, int* index, Pokedex *pokedex){
	for(int i = 0; i < pokedex->num_of_pokemons; i++){
		if(!strcmp(pokemon_str, pokedex->pokemons[i]->name)){
			*index = i;
			return success;
		}
	}
	return failure;
}

// CREATING TYPES POINTER ARRAY
void create_types(char *str, int num_of_types, Pokedex *pokedex){
	pokedex->types = (Type**) malloc(sizeof(Type*)*num_of_types);
	if(NULL == pokedex->types){
		printf("Memory problem\n");
		unload_Pokedex(pokedex);
	}
	for(int i = 0; i< num_of_types;i++)
		pokedex->types[i] = NULL;

	char** types_str = slice_str(str, ",");
	Type *type = NULL;

	for(int i = 0; i < num_of_types; i++){
		type = (Type*) malloc(sizeof(Type));
		if(NULL == type) {
			free(types_str);
			unload_Pokedex(pokedex);
			return;
		}
		// --init the fields--
		type->name = types_str[i];
		type->num_of_pokemons = 0;
		type->effective_me = (Type**) malloc(sizeof(Type*));
		type->effective_other = (Type**) malloc(sizeof(Type*));

		type->effective_me[0] = NULL;
		type->effective_other[0] = NULL;

		pokedex->types[i] = type;
		pokedex->num_of_types++;
	}
	free(types_str);
}

void unload_Types(Type** types, int num_of_types){
	int i;
	for(i = 0; i < num_of_types; i++){
		free(types[i]->effective_me);
		free(types[i]->effective_other);
		free(types[i]);
	}
	free(types);
}

void unload_Pokemons(Pokemon** pokemons, int num_of_pokemons){
	for(int i = 0; i < num_of_pokemons; i++){
		free(pokemons[i]->Bio_Info);
		free(pokemons[i]);
		pokemons[i] = NULL;
	}
	free(pokemons);
}


void unload_Pokedex(Pokedex *pokedex){
	unload_Types(pokedex->types, pokedex->num_of_types);
	free(pokedex);
}

// Boolean method
// typdefs:
//		effect_side{me, other}
//		operation_effect{remove, add}
// the typedef print and enter cases accordindly
// that way we can do all the operation's Only by one function by relaing on the inputs

status typeA_effect_typeB(int typeA, int typeB, pick_side effect_side, operation effect_operation, Pokedex *pokedex){
	int found;
//	 effect_opt{remove = 0, add = 1}
//	 effect_side{me, other} ----> type->effect_mat[typeB = indexB] =(int) (me, other)
	switch(effect_operation){
		case add:
		{
			switch(effect_side){
				case me:
				{
					if(search_effect_str(pokedex->types[typeA]->effective_me, pokedex->types[typeB]->name) == -1){
						if((pokedex->types[typeA]->effective_me = add_effect(pokedex->types[typeB], pokedex->types[typeA]->effective_me))==NULL)
							return failure;
						return success;
					}
					else return failure;
					break;
				}
				case other:
				{
					if(search_effect_str(pokedex->types[typeA]->effective_other, pokedex->types[typeB]->name) == -1){
						if((pokedex->types[typeA]->effective_other = add_effect(pokedex->types[typeB], pokedex->types[typeA]->effective_other))== NULL)
							return failure;
						return success;
					}
					else return failure;
					break;
				}
				default: break;
			}
			break;
		}
		case rm:
		{
			switch(effect_side){
			case me:
			{
				found = search_effect_str(pokedex->types[typeA]->effective_me, pokedex->types[typeB]->name);
				if(found != -1){
						if((pokedex->types[typeA]->effective_me = remove_effect(found, pokedex->types[typeA]->effective_me))==NULL)
							return failure;
						return success;
				}
				else return failure;
				break;
			}
			case other:
			{
				found = search_effect_str(pokedex->types[typeA]->effective_other, pokedex->types[typeB]->name);

				if(found != -1){
					if((pokedex->types[typeA]->effective_other = remove_effect(found, pokedex->types[typeA]->effective_other))==NULL)
						return failure;
					return success;
				}
				else return failure;
				break;
				}
			default :break;

			}
		break;
		}
		default :break;
	}
	return failure;
}


Type** add_effect(Type* type, Type** effects){
	int i;
	Type** new_effects;
	for(i = 0; effects[i] != NULL; i++);
	effects[i] = type;
	new_effects = realloc(effects, sizeof(Type*)*(i+2));
	if(new_effects == NULL){
		printf("Memory problem\n");
		return NULL;
	}
	new_effects[i+1] = NULL;
	effects = NULL;
	return new_effects;

}

Type** remove_effect(int type_index, Type** effects){
	int i;
	for(i = type_index; effects[i] != NULL; i++)
		effects[i] = effects[i+1];
	Type** new_effects;
	new_effects = realloc(effects, sizeof(Type*)*i);
	return new_effects;
}

int search_effect_str(Type** effects, char* eff){
	int i;
	for(i = 0; effects[i] != NULL; i++)
		if(!strcmp(effects[i]->name, eff))
			return i;
	return -1;
}

// CREATING POKEMONS ARRAY
// pokemon_str = will be all the data got from text, we will start our reading from i->[start, num_of_pokemons]
//				for each line send for pokemon create (name, specie, height, weight, attacl, type)
//	return the Pokemons array created
void create_Pokemons(char **pokemon_str, int num_of_pokemons, int start, Pokedex *pokedex){
	pokedex->pokemons = (Pokemon**) malloc(sizeof(Pokemon*)*num_of_pokemons);
	if(pokedex->pokemons == NULL){
		printf("Memory problem\n");
		unload_Pokedex(pokedex);
	}
	for(int i = 0; i < num_of_pokemons; i++)
		pokedex->pokemons[i] = NULL;
	Pokemon *created_pokemon;
	int end = start + num_of_pokemons;
	char **data;
	for(int i = start; i < end; i++){
		if(*(pokemon_str+i) == NULL){
			return;
		}
		data = slice_str(*(pokemon_str+i), ",");
		if(data == NULL || data[0] == NULL || data[1] == NULL || data[2] == NULL || data[3] == NULL || data[4] == NULL){
			free(data);
			return;
		}

		created_pokemon = create_pokemon(data[0], data[1], data[2], data[3], data[4]);
		if(created_pokemon == NULL)
			return;


		pokedex->pokemons[i - start] = created_pokemon;
		pokedex->num_of_pokemons++;

		int index;
		index = search_type(data[5], pokedex);

		created_pokemon->type = pokedex->types[index];
		pokedex->types[index]->num_of_pokemons++;


		free(data);
	}
	return;
}

// Creating pokemon
Pokemon* create_pokemon(char* name, char* specie, char* height_str, char* weight_str, char* attack_str){

	B_Info *Bio_Info = (B_Info*) malloc(sizeof(B_Info));
	if(Bio_Info == NULL)
		return NULL;


	float weight, height;
	int attack;

	// Turn str for int or float may cause errors cause the float add number at 0.000000000000024324
	height = strtod(height_str, NULL);
	weight = strtod(weight_str, NULL);
	attack = strtol(attack_str, NULL, 10);

	// If i won't be lazy write function for this.
	// set the Biological Information fields
	Bio_Info->attack = attack;
	Bio_Info->height = height;
	Bio_Info->weight = weight;

	Pokemon *ppokemon = (Pokemon*) malloc(sizeof(Pokemon));
	if(ppokemon == NULL)
		return NULL;


	// set the pokemon Field nothing special
	ppokemon->Bio_Info = Bio_Info;
	ppokemon->name = name;
	ppokemon->specie = specie;

	return ppokemon;
}

// creating Pokemon not with the standard method
// ** different template
Pokemon* createPokemonInsert(char* pokemon, Pokedex* pokedex){
	char** pokemon_data = slice_str(pokemon, ",");
	Pokemon* newPokemon = create_pokemon(pokemon_data[1], pokemon_data[2], pokemon_data[3], pokemon_data[4], pokemon_data[5]);
	if(newPokemon == NULL) return NULL;
	newPokemon->type  = pokedex->types[search_type(pokemon_data[0], pokedex)];
	free(pokemon_data);

	return newPokemon;
}

// slicing string given the num of subs and the char type to sparate with
// need to understand how not to rely on num_of_subs, how can i count and malloc the size needed?????
char** slice_str(char* str, char* del){
	  char *ch;
	  int sub_str_count = 2;
	  int length = strlen(str);
	  int p_iter = 1;
	  if(length == 0)
		  return NULL;
	  if(str[length-1] == '\r')
		  str[length-1] = '\0';
	  for(int i = 0; i < length; i++)
		  if(str[i] == del[0])
			  sub_str_count++;

	  char** elements  = (char**) malloc(sizeof(char*)*sub_str_count);
	  ch = strtok(str, del);
	  elements[0] = ch;
	  while (ch != NULL) {
		  ch = strtok(NULL, del);
		  elements[p_iter] = ch;
		  p_iter++;
	  }
	  elements[sub_str_count-1] = NULL;


	return elements;
}
