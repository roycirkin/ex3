
# ex3


int this project we has to create a cache-manager who knows how to solve matrix problems, calculate crc
and doing a few operation ob bmp images.


# implementation

 - the cache before each operation checks if that task was asked by the user before, and if it does so  he brings 
 the user the solution to his task from the cache(cache heat)
- the cache alaways saved the most recently used files by the user and deletes the file who wasnt used for 
the longest time
- cache clear deletes all the files in the cache
- cache search returs us either the task we want is saved in the cache or not. if it does than the
cache manager tells us when this task was saved on the cache, and it can also tell us when was it last used.


# design

 * before each of the operations, the cache-manager builds his lru_list from the files in the cache directory.
 each file contains in it's start his saved time, when he was used last time and more information on himself
as well as his content (the solution to a previous operation given by the user).

* then if the cache manager finds in one of his lru node that he has already done that operation before, 
than he returns us the answer from the file which is associated with the lru node. otherwise he solves the 
given problem and saves it on a new file in the cache directory.
