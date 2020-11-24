# lem_in
The purpose of this project is to find paths from start to end and guide the ants along them in the least number of steps.
## Algorithms
### BFS (breadth-first search)
* Detecting if there is a path from start to finish (On a graph without rooms with duplicates).

[More details about BFS](https://foxford.ru/wiki/informatika/algoritm-poiska-v-shirinu)

### Suurballe
* Create duplicates of each room (except start and end)
* Convert undirected graph to directed graph

[More details about Suurballe](http://www.macfreek.nl/memory/Disjoint_Path_Finding)

### Bellman-Ford
*	Finding path from start to end
*	This algorithm is used because the graph can have negative edge weights

[More details about Bellman-Ford](https://foxford.ru/wiki/informatika/algoritm-forda-bellmana)

## How to download ?
```
git clone https://github.com/fallard21/lem_in.git ~/lem-in
cd ~/lem-in
```

## How to use?
* Build project with `make -C .`
* `./lem-in < MAP_FILE`

## Bonus
*	`--help`	- output manual
*	`--stat`	- output only found paths and graph statistic
*	`--map`		- output only map from file _(enabled by default)_
*	`--move`	- output only moving ants (for easy check steps `wc -l`) _(enabled by default)_
*	`--all`		- use all options (except --help)
*	Detailed error management

## Speed test
*	Max ~1.5 seconds on `--big-superposition` _(5k rooms)_
