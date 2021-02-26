#compilateur
CC = g++

DBG = no
CFLAGS = -g -Wall -O2

# assemblage des infos de lib. et inc.
lib = $(libG2X)

src = src/
inc = -I./include $(incG2X) 

%.o : $(src)%.cpp
	@echo "module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"
	
% : %.o 
	@echo "edition de lien $^ -> $@"
	@$(CC) $^ $(lib) -o $@
	
Corde : PMat.o Link.o Corde.o
	@echo "edition de lien $^ -> $@"
	@$(CC) $^ $(lib) -o $@

.PHONY : clean cleanall

clean : 
	rm -f *.o .tmp*
cleanall : 
	rm -f *.o .tmp* $(EXEC)
