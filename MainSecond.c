/*
 * MainFirst.c
 *
 *  Created on: Nov 17, 2021
 *      Author: ise
 */


#include "Defs.h"
#include "BattleByCategory.h"
#include "Pokemon.h"

static char **data;
static int num_of_lines;
status loadFile(int num_of_types, int num_of_pokemons,char* STARTUP, int *pokemons_Start);
void unloadData(int num_of_pokemons);
void loadInput(char* Input, char* buffer, int *InputIter);


int main(int argc, char* argv[]){

	int command, PowerON;
	command = 0;
	char ch;
	char* buffer = NULL;

	char Input[300];
	int inputIter = 0;
	// will be used for case 3, 4 , 5, 6 typeA->typeB

	int num_of_pokemons, capacity, num_of_types, pokemonStart;
	capacity = atoi(argv[2]);
	num_of_types = atoi(argv[1]);
	if(loadFile(capacity, num_of_types, argv[3], &pokemonStart) == failure){
		unloadData(0);
		printf("No memory available.\n");
		return 0;
	}

	Battle battle = NULL;

	if(num_of_types == 0)
		battle = createBattleByCategory(capacity, 0, "", *equalPokemonsAttack, *copyPokemon, *freePokemon , *getType, *getPokemonsAttack, *printPokemon);
	else
		battle = createBattleByCategory(capacity, num_of_types, data[1], *equalPokemonsAttack, *copyPokemon, *freePokemon, *getType, *getPokemonsAttack, *printPokemon);


	if(battle == NULL){
		unloadData(0);
		printf("No memory available.\n");
		return 0;
	}

	num_of_pokemons = num_of_lines - pokemonStart;
	Pokedex* pokedex = create_Pokedex(data, num_of_pokemons, num_of_types, pokemonStart, num_of_lines);
	if(pokedex == NULL){
		destroyBattleByCategory(battle);
		unloadData(0);
		printf("No memory available.\n");
		return 0;
	}

	num_of_pokemons = pokedex->num_of_pokemons;

	for(int i = 0; i < num_of_pokemons; i++){
		if(insertObject(battle, pokedex->pokemons[i]) == failure){
			destroyBattleByCategory(battle);
			unloadData(i);
			unload_Pokedex(pokedex);
			printf("No memory available.\n");
			return 0;
		}
		free(data[num_of_lines - num_of_pokemons + i]);
	}

	unload_Pokemons(pokedex->pokemons, num_of_pokemons);

	PowerON = 1;
	do{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");


		ch = getchar();
		if(ch == '\n')
			ch = getchar();
		command = ((int) ch) - 48;
		if(!isdigit(ch) || command < 1 || command > 6){
			printf("Please choose a valid number.\n");
			command = 0;
		}

		switch(command){
		case 1: /* Print All Pokemon*/
		{
			displayObjectsByCategories(battle);
			break;
		}

		case 2:
		{
			print_all_types(pokedex);
			break;
		}

		case 3:
		{

			int type_index =0;
			printf("Please enter Pokemon type name:\n");
			scanf("%s", Input);

			if((type_index = search_type(Input, pokedex)) == -1)
				printf("Type name doesn't exist.\n");
			else if(getNumberOfObjectsInCategory(battle, Input) == capacity)
				printf("Type at full capacity.\n");

			else {
				buffer = (char*) malloc(sizeof(char)*300);
				if(buffer == NULL){
					destroyBattleByCategory(battle);
					unloadData(num_of_pokemons);
					unload_Pokedex(pokedex);
					printf("No memory available.\n");
					return 0;
				}

				else{
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon name:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon species:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon height:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon weight:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon attack:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					buffer[inputIter] = '\0';
					Pokemon* newPokemon = createPokemonInsert(buffer, pokedex);
					if(newPokemon == NULL){
						free(buffer);
						destroyBattleByCategory(battle);
						unloadData(num_of_pokemons);
						unload_Pokedex(pokedex);
						printf("No memory available.\n");
						return 0;
					}
					if(insertObject(battle, newPokemon) == failure){
						freePokemon(newPokemon);
						free(buffer);
						destroyBattleByCategory(battle);
						unloadData(num_of_pokemons);
						unload_Pokedex(pokedex);
						printf("No memory available.\n");
						return 0;
					}

					inputIter = 0;
					pokedex->types[type_index]->num_of_pokemons++;
					printf("The Pokemon was successfully added.\n");
					printPokemon(newPokemon);
					free(newPokemon->Bio_Info);
					free(newPokemon);
					free(buffer);

				}
			}
			break;
		}

		case 4:
		{
			int type_index = 0;

			printf("Please enter type name:\n");
			scanf("%s", Input);

			if((type_index = search_type(Input, pokedex)) == -1)
				printf("Type name doesn't exist.\n");

			else if(getNumberOfObjectsInCategory(battle, Input) > 0)
			{
					Pokemon* toPrint = (Pokemon*) removeMaxByCategory(battle, Input);
					printf("The strongest Pokemon was removed:\n");
					print_Pokemon(toPrint);
					freePokemon(toPrint);
					pokedex->types[type_index]->num_of_pokemons--;

			}
			else
				printf("There is no Pokemon to remove.\n");

			break;
		}

		case 5:
		{
			printf("Please enter Pokemon type name:\n");
			scanf("%s", Input);

			if(search_type(Input, pokedex) == -1)
				printf("Type name doesn't exist.\n");

			else{

				buffer = (char*) malloc(sizeof(char)*300);
				if(buffer == NULL){
					destroyBattleByCategory(battle);
					unloadData(num_of_pokemons);
					unload_Pokedex(pokedex);
					printf("No memory available.\n");
					return 0;
				}

				else{
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon name:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon species:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon height:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon weight:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					printf("Please enter Pokemon attack:\n");
					scanf("%s", Input);
					loadInput(Input, buffer, &inputIter);
					buffer[inputIter] = '\0';
					Pokemon* choosenPokemon = createPokemonInsert(buffer, pokedex);
					if(choosenPokemon == NULL){
						free(buffer);
						destroyBattleByCategory(battle);
						unloadData(num_of_pokemons);
						unload_Pokedex(pokedex);
						printf("No memory available.\n");
						return 0;
					}
					printf("You choose to fight with:\n");
					printPokemon(choosenPokemon);
					fight(battle, choosenPokemon);
					free(choosenPokemon->Bio_Info);
					free(choosenPokemon);
					free(buffer);
					inputIter = 0;
				}
			}
			break;
		}
		case 6:
			PowerON = 0;
			break;


		default: break;

		}
	}while(PowerON);

	destroyBattleByCategory(battle);
	unload_Pokedex(pokedex);
	unloadData(num_of_pokemons);
	printf("All the memory cleaned and the program is safely closed.\n");
	return 0;
}

void loadInput(char* Input, char* buffer, int *InputIter){
	int n = strlen(Input);
	buffer[*InputIter]= ',';
	(*InputIter) = *InputIter + 1;
	for(int i = 0; i < n; i++)
		buffer[(*InputIter)++] = Input[i];
}

void unloadData(int num_of_pokemons){
	for(int i = 0; i < num_of_lines-num_of_pokemons; i++)
		free(data[i]);
	free(data);
}

B_Info* createBio(int attack, float weight, float height){
	B_Info *Bio_Info = (B_Info*) malloc(sizeof(B_Info));
		if(Bio_Info == NULL)
			return NULL;

		// If i won't be lazy write function for this.
		// set the Biological Information fields
		Bio_Info->attack = attack;
		Bio_Info->height = height;
		Bio_Info->weight = weight;

		return Bio_Info;
}

status printPokemon(element elem){
	if(elem == NULL) return failure;
	Pokemon* pokemon = (Pokemon*) elem;
	print_Pokemon(pokemon);
	return success;
}

status loadFile(int num_of_types, int num_of_pokemons,char* STARTUP, int *pokemons_Start){
	FILE* config = fopen(STARTUP , "r");
	if(config == NULL){
		return failure;
	}

	int lineIter = 0, reader =0;
	char buffer1[300], *buffer;


	// create all known size of types, pokemons, effective etc..
	int max_traits;

	// calculate the max Lines possiable in the configrution file
	max_traits = num_of_types*num_of_types*2;
	num_of_lines = num_of_types + num_of_pokemons*num_of_types + max_traits + 2;

	// Pointer array to each line in the end of scanning under!
	data = (char**) malloc(sizeof(char*)*(num_of_lines+1));
	if(data == NULL){
		fclose(config);
		return failure;
	}

	int eof_flag = 0;
	if(num_of_lines > 2)
	do{
		char c= fgetc(config);

		if(feof(config))
			eof_flag = 1;

		if((int) c != 9)
			buffer1[reader++] = c;

		if(c == '\n' || c == EOF){
			buffer1[reader-1] = '\0';
			// find where the line of Pokemons creation will start
			if(strcmp(buffer1, "Pokemons\r") == 0 || strcmp(buffer1, "Pokemons") == 0)
				*pokemons_Start = lineIter + 1;

			// allocate memory for each line and point lines pointer at lineIter index
			// reset our reader
			buffer = (char*) malloc(sizeof(char)*(strlen(buffer1)+1));
			strcpy(buffer, buffer1);
			data[lineIter++] = buffer;

			// my miserable way to handle EOF char that ruined my evnning
			if(eof_flag)
				break;

			if(buffer == NULL){
				fclose(config);
				free(buffer);
				return failure;
			}
			reader = 0;
		}

	}while(lineIter < num_of_lines);
	else free(buffer);

	num_of_lines = lineIter;
	fclose(config);
	return success;
}


int equalPokemonsAttack(element poke1, element poke2){
	Pokemon* pokemon1 = (Pokemon*) poke1;
	Pokemon* pokemon2 = (Pokemon*) poke2;

	if(pokemon1->Bio_Info->attack > pokemon2->Bio_Info->attack)
		return 1;
	if(pokemon1->Bio_Info->attack < pokemon2->Bio_Info->attack)
		return -1;
	return 0;
}

element copyPokemon(element poke){
	if(poke == NULL)
		return NULL;

	Pokemon* pokemon = (Pokemon*) poke;

	Pokemon* pokemoncpy = (Pokemon*) malloc(sizeof(Pokemon));
	if(pokemoncpy == NULL)
		return NULL;

	B_Info* Bio_Info = createBio(pokemon->Bio_Info->attack, pokemon->Bio_Info->weight, pokemon->Bio_Info->height);
	if(Bio_Info == NULL) return NULL;
	pokemoncpy->Bio_Info = Bio_Info;
	pokemoncpy->specie = (char*) malloc(sizeof(char)* (strlen(pokemon->specie) + 1));
	strcpy(pokemoncpy->specie, pokemon->specie);
	pokemoncpy->name = (char*) malloc(sizeof(char)*(strlen(pokemon->name)+1));
	strcpy(pokemoncpy->name, pokemon->name);
	pokemoncpy->type = pokemon->type;

	return pokemoncpy;
}

char* getType(element poke){
	if(poke == NULL) return NULL;
	Pokemon* pokemon = (Pokemon*) poke;
	return pokemon->type->name;
}

int getPokemonsAttack(element firstElem, element secondElem, int* attackFirst,int* attackSecond){

	Pokemon* pokemon1 = (Pokemon*) firstElem;
	Pokemon* pokemon2 = (Pokemon*) secondElem;

	*attackFirst = pokemon1->Bio_Info->attack;
	*attackSecond = pokemon2->Bio_Info->attack;

	if(search_effect_str(pokemon1->type->effective_me, pokemon2->type->name) != -1)
		*attackFirst = *attackFirst - 10;
	else if(search_effect_str(pokemon2->type->effective_other, pokemon1->type->name) != -1)
		*attackFirst = *attackFirst - 10;

	if(search_effect_str(pokemon2->type->effective_me, pokemon1->type->name) != -1)
			*attackSecond = *attackSecond - 10;
	else if(search_effect_str(pokemon1->type->effective_other, pokemon2->type->name) != -1)
		*attackSecond = *attackSecond - 10;

	return *attackFirst - *attackSecond;
}

status freePokemon(element Elem){
	if(Elem == NULL) return failure;
	Pokemon* pokemon = (Pokemon*) Elem;
	free(pokemon->Bio_Info);
	free(pokemon->name);
	free(pokemon->specie);
	free(pokemon);
	return success;
}
