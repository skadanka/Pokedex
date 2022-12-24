CC=gcc
OBJS=Pokemon.o MainSecond.o BattleByCategory.o LinkedList.o MaxHeap.o
EXEC=PokemonsBattles
DEBUG_FLAG=-g 
COMP_FLAG=-c
CLEAN=clean
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
Pokemon.o : Pokemon.c Defs.h Pokemon.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
MainFirst.o : MainSecond.c Defs.h Pokemon.h BattleByCategory.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
MaxHeap.o :  MaxHeap.c MaxHeap.h Defs.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
LinkedList.o : LinkedList.c LinkedList.h Defs.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
BattleByCategory.o : BattleByCategory.c LinkedList.h MaxHeap.h BattleByCategory.h Defs.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
