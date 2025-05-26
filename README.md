# GameOfLife.c
[Conway's Game of Life](playgameoflife.com) implementation in C.
Project Details [here](https://site-pa.netlify.app/proiecte/game_of_life/)
# Functions
## Task 1 
```
gaseste_vecini                      # takes a grid and the coordinates of a cell within, outputs the number of live cells around it
populare_grila                      # initializes the matrix of the first generation, using the contents of the input file
afisare_grila                       # writes the matrix of a generation to the output files
```
## Task 2
```
creare_celula                       # initializes a list node
adaugare_celula                     # adds the initialized cell to the list
eliberare_lista                     # frees the memory allocated for the list
creare_generatie                    # creates the stack of lists
adaugare_generatie                  # adds a list to the stack
inversare_stiva                     # reverses the stack (because the first element pushed into the stack is the last to get popped out, it needs reversing for proper output)
eliberare_stiva                     # frees memory allocated for the stack
```
## Task 3
```
gaseste_vecini_T3                   # same as the function from Task 1, takes char* instead of char**
afisare_grila_T3                    # same as the function from Task 1, takes char* instead of char**
construire_arbore                   # creates the tree
copiaza_grila                       # creates a deep copy of the matrix you call it with, returns a char*
apply_rule_B                        # applies rule B (any cell with exactly 2 neighbors remains/becomes alive) for a given matrix
apply_classic_rule                  # applies the classic rule set for a given matrix
furnizare_lista_celule_diferite     # takes the current generation matrix and the next generation matrix, returns a linked list containing coordinates of the different cells
parcurgere_preordine                # preoder traversal of the tree
aplica_diferente                    # takes a list of different cells and a matrix, and changes cell states based on the cells in the list
eliberare_arbore                    # frees the memory allocated for the tree
```
## Task 4
```
parcurgere_preordine_T4             # preoder traversal, similar to that of Task 3, root processing is different
void DFS                            # performs (or tries to perform) a Depth-First Search within a graph, using the adjacency matrix, updates the longest hamiltonian chain (if found)
gaseste_lant_hamiltonian            # calls DFS function for all nodes of the graph, then outputs the chain length and path followed
```
