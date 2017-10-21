#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "songs.h"

void print_song(struct song_node* song){
  if(song){
    printf("%s: %s", song -> artist, song -> name);
    printf("\n");
  }
}

void print_songs(struct song_node* song){
  while(song){
    printf("%s: %s", song -> artist, song -> name);
    printf(" | ");
    song = song -> next;
  }
  printf("\n");
}

struct song_node* insert_front(struct song_node * song, char* artist, char* name){
  struct song_node * new_song = (struct song_node *) malloc(sizeof(struct song_node));
  strcpy(new_song -> artist, artist);
  strcpy(new_song -> name, name);
  new_song -> next = song;
  return new_song;
}

struct song_node* free_list(struct song_node* song){
  struct song_node* next_song;
  while(song){
    next_song = song -> next;
    free(song);
    song = next_song;
  }
  return song;
}

struct song_node* find_artist(struct song_node* song, char* artist){
  printf("looking for [%s]\n", artist);
  while(song){
    if(strcmp(song -> artist, artist) == 0){
      printf("  artist found! ");
      print_songs(song);
      printf("\n");
      return song;
    }
    song = song -> next;
  }
  printf("  artist not found ");
  print_songs(song);
  printf("\n");
  return song;
}

struct song_node* find_song(struct song_node* song, char* artist, char* name){
  printf("looking for [%s: %s]\n", artist, name);
  struct song_node* found_artist = find_artist(song, artist);
  while(found_artist){
    if(songcmp(found_artist -> artist, found_artist -> name, artist, name) == 0){
      printf("  song found! ");
      print_song(found_artist);
      printf("\n");
      return found_artist;
    }
    found_artist = found_artist -> next;
  }
  printf("  song not found ");
  print_song(found_artist);
  printf("\n");
  return found_artist;
}

int songcmp(char* artist_one, char* name_one, char* artist_two, char* name_two){
  printf("comparing [%s: %s] to [%s: %s]\n", artist_one, name_one, artist_two, name_two);
  if(strcmp(artist_one, artist_two) == 0){
    return strcmp(name_one, name_two);
  }
  return strcmp(artist_one, artist_two);
}

/*
  int songcmp(struct song_node* song_one, struct song_node* song_two){
  return strcmp(song_one -> artist, song_two -> artist) + strcmp(song_one -> name, song_two -> name);
  }
*/

int get_num(struct song_node* song){
  int number_song = 0;
  while(song){
    song = song -> next;
    number_song++;
  }
  return number_song;
}

struct song_node* random_song(struct song_node* song){
  int number = get_num(song);
  int rand_num = rand() % number;
  while(rand_num){
    song = song -> next;
    rand_num -= 1;
  }
  rand_num = rand() % number;
  return song;
}

struct song_node* remove_song(struct song_node* song, char* artist, char* name){
  printf("removing [%s: %s]\n", artist, name);
  
  struct song_node* target;
  //case 1: first song needs to be removed
  if(songcmp(song -> artist,song -> name, artist, name) == 0){
    target = song;
    song = target -> next;
    free(target);
    return song;
  }

  //case 2: second song + needs to be removed
  target = song -> next;
  while(target){//iterate through all the songs
    if(songcmp(target -> artist, target -> name, artist, name) == 0){
      song -> next = target -> next;
      free(target);
      return song;
    }
    song = target;
    target = song -> next;
  }

  //case 3: song does not exist
  return song;
}

int main(){

  struct song_node * song = (struct song_node *) malloc(sizeof(struct song_node));
  strcpy(song -> artist, "ac/dc");
  strcpy(song -> name, "thunderstruck");
  song -> next = NULL;

  song = insert_front(song, "radiohead", "street spirit (fade out)");
  song = insert_front(song, "radiohead", "paranoid android");
  song = insert_front(song, "pink floyd", "time");
  song = insert_front(song, "pearl jam", "yellow ledbetter");
  song = insert_front(song, "pearl jam",  "even flow");
  song = insert_front(song, "pearl jam",  "alive");
  
  printf("LINKED LIST TESTS");
  printf("\n====================================\n\n");
    
  printf("Testing print_songs:\n");
  print_songs(song);
  printf("====================================\n\n");
  
  printf("Testing print_song:\n");
  print_song(song);
  printf("====================================\n\n");

  printf("Testing find_song:\n");
  struct song_node* found = find_song(song, "pearl jam", "yellow ledbetter");
  find_song(song, "pearl jam", "daughter");
  printf("====================================\n\n");

  printf("Testing find_artist:\n");
  struct song_node* song_one = find_artist(song, "pearl jam");
  struct song_node* song_two = song_two = find_artist(song, "radiohead");
  find_artist(song, "presidents of the united states of america");
  printf("====================================\n\n");
  
  printf("Testing songcmp (helper function):\n");
  printf("  %d\n", songcmp(song_one -> artist, song_one -> name, song_one -> artist, song_one -> name));
  printf("  %d\n", songcmp(song_one -> artist, song_one -> name, song_two -> artist, song_two -> name));
  printf("  %d\n", songcmp(song_two -> artist, song_two -> name, song_one -> artist, song_one -> name));
  printf("====================================\n\n");
    
  printf("Testing random:\n");
  srand(time(NULL));
  print_song(random_song(song));
  print_song(random_song(song));
  print_song(random_song(song));
  print_song(random_song(song));
  print_song(random_song(song));
  print_song(random_song(song));
  printf("====================================\n\n");
  
  printf("Testing remove:\n");
  remove_song(song, "pink floyd", "time");
  printf("\n");
  remove_song(song, "pink floyd", "time");

  printf("\n");
  remove_song(song, "ac/dc", "thunderstruck");
  print_songs(song);
  printf("\n====================================\n\n");
  
  printf("Testing free_list:\n");
  print_songs(song);
  song_one = free_list(song);
  printf("list after free_list:\n");
  print_songs(song_one);
  printf("memory that has been freed, but not cleared:\n");
  print_songs(song);
  printf("\n====================================\n\n");
  
  return 0;
}
