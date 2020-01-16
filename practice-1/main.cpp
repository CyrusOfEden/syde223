// *********************************************************
//
// SYDE 223: Practice Assignment 1
//
// Group members:
// Alex Dales - 20770792
// Kash Nouroozi -
//
// Due Date: Friday, Jan 17 at 10:30 AM
//
// *********************************************************

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

class Music {
    string music_id;
    string artist_name;
    unsigned int year;

public:

    Music() : music_id(""), artist_name(""), year(0) {}

    Music(string new_music_id, string new_artist_name, unsigned int new_year)
            : music_id(new_music_id), artist_name(new_artist_name), year(new_year) {}

    string get_artist_name() {
        return artist_name;
    }

    bool operator==(const Music &m) {
        bool equal = true;
        equal = equal && (m.music_id == music_id);
        equal = equal && (m.artist_name == artist_name);
        equal = equal && (m.year == year);
        return equal;
    }

    void print() {
        cout << "Music ID: " << music_id << " | Artist Name: " << artist_name << " | Year: " << year;
    }
};

class Song : public Music {
    string name;
    string genre;
    unsigned int duration;

public:

    Song() : Music(), name(""), genre(""), duration(0) {}

    Song(Music new_music, string new_name, string new_genre, unsigned int new_duration)
            : Music(new_music), name(new_name), genre(new_genre), duration(new_duration) {}

    bool operator==(const Song &s) const {
        bool equal = true;
        equal = equal && (s.genre == genre);
        equal = equal && (s.name == name);
        equal = equal && (s.duration == duration);
        equal = equal && static_cast<Music>(*this) == static_cast<Music>(s);
        return equal;
    };

    void print() {
        cout << "Name: " << name << " | Genre: " << genre << " | Duration : " << duration << " minutes \n";
        static_cast<Music>(*this);
    }
};

const int max_playlist_songs = 3;

class Playlist {
    vector<Song> my_playlist;

public:

    bool insert_song(Song &song) {
        int songs_by_this_artist = 0;
        for (Song s : my_playlist) {
            if (s == song) {
                return false;
            }

            if (s.get_artist_name() == song.get_artist_name()) {
                songs_by_this_artist++;
                if (songs_by_this_artist == max_playlist_songs) {
                    return false;
                }
            }
        }

        my_playlist.push_back(song);
        return true;
    }

    Playlist shuffle_songs() {

        Playlist shuffled_playlist;

        vector<Song> copied_playlist(my_playlist);

        while (copied_playlist.size() > 0) {
            int index = rand() % copied_playlist.size();
            shuffled_playlist.my_playlist.push_back(copied_playlist.at(index));
            copied_playlist.erase(copied_playlist.begin() + (index));
        }

        return shuffled_playlist;
    }

    Song get_song(int i) {
        return my_playlist[i];
    }

    void print() {
        for (int i = 0; i < my_playlist.size(); i++) {
            my_playlist.at(i).print();
        }
    }

    friend Playlist operator+(Playlist &p1, Playlist &p2);
};


Playlist operator+(Playlist &p1, Playlist &p2) {
    Playlist combined_playlist;
    combined_playlist.my_playlist = p1.my_playlist;

    for (int i = 0; i < p2.my_playlist.size(); i++) {
        combined_playlist.my_playlist.push_back(p2.my_playlist.at(i));
    }

    return combined_playlist;
}

// INPUT: None
// PURPOSE: Tests the insert song function:
// 1. Checks if songs are inserted into the playlist.
// 2. Checks if the function inserts a duplicate song or not.
// 3. Checks if the function inserts more than three songs by the same artist
// OUTPUT: True or false, based on running_tests
bool test_insert_song() {

    bool running_tests = false;

    Music music_1 = Music("testId", "Playboi Carti", 2020);

    Song song_1 = Song(music_1, "Long time", "Rap", 2);
    Song song_2 = Song(music_1, "Shoota", "Rap", 4);
    Song song_3 = Song(music_1, "Mileage", "Rap", 5);
    Song song_4 = Song(music_1, "Poke it out", "Rap", 2);

    Playlist playlistOne;

    playlistOne.insert_song(song_1);

    if (playlistOne.get_song(0) == song_1) {
        running_tests = true;
        // cout << "Test 1.0: PASSED - Song was inserted successfully. \n";
    } else {
        running_tests = false;
        cout << "Test 1.0: FAILED - Song was not inserted successfully. \n";
    }

    playlistOne.insert_song(song_1);

    if (playlistOne.get_song(1) == song_1) {
        running_tests = false;
        cout << "Test 1.1: FAILED - Song duplicate was inserted. \n";
    } else {
        running_tests = running_tests && true;
        // cout << "Test 1.1: PASSED - Song duplicate was not inserted. \n";
    }

    playlistOne.insert_song(song_2);
    playlistOne.insert_song(song_3);
    playlistOne.insert_song(song_4);

    if (!(playlistOne.get_song(3) == song_4)) {
        running_tests = running_tests && true;
        // cout << "Test 1.2: PASSED - Fourth song by the same artist was not added. \n";
    } else {
        running_tests = false;
        cout << "Test 1.2: FAILED - Fourth song by the same artist was added. \n";
    }

    return running_tests;
}

// INPUT: None
// PURPOSE: Tests the shuffle_playlist function
// 1. Checks if a playlist's songs are shuffled once the function is called
// OUTPUT: True or false, based on running_tests
bool test_shuffle_playlist() {

    bool running_tests = false;

    Music music_1 = Music("testId", "Mac Miller", 2020);
    Music music_2 = Music("testId", "Drake", 2017);

    Song song_1 = Song(music_1, "Good News", "Rap", 5);
    Song song_2 = Song(music_1, "Best Day Ever", "Rap", 2);
    Song song_3 = Song(music_1, "Nikes on my Feet", "Rap", 4);
    Song song_4 = Song(music_2, "Now and Forever", "Rap", 3);

    Playlist playlistTwo;

    playlistTwo.insert_song(song_1);
    playlistTwo.insert_song(song_2);
    playlistTwo.insert_song(song_3);
    playlistTwo.insert_song(song_4);

    Playlist shuffled_playlist_test = playlistTwo.shuffle_songs();

    Playlist test_shuffled_playlist = playlistTwo.shuffle_songs();

    // checks every index of the shuffled playlist and compares it to the same index of the non-shuffled playlist
    // to see if at least one of the index's are different compared to the original playlist, in which case it would have shuffled
    if ((!(test_shuffled_playlist.get_song(0) == playlistTwo.get_song(0))) ||
        (!(test_shuffled_playlist.get_song(1) == playlistTwo.get_song(1))) ||
        (!(test_shuffled_playlist.get_song(2) == playlistTwo.get_song(2))) ||
        (!(test_shuffled_playlist.get_song(3) == playlistTwo.get_song(3)))) {
        running_tests = running_tests && true;
    } else {
        running_tests = false;
    }

    return running_tests;
}

// INPUT: None
// PURPOSE: Runs all the test functions and checks if they all pass, then outputs that "All the test functions have passed."
//          if the if statement is met.
// OUTPUT: Void
void run() {

    bool tests_passed = false;

    test_insert_song();
    test_shuffle_playlist();

    // checks if all the tests have passed
    if (test_shuffle_playlist() == true && test_insert_song() == true) { //insert the two other tests functions
        tests_passed = true;
    }
    if (tests_passed = true) {
        cout << "All the test functions have passed.";
    }
}

int main() {
    srand(time(0));
    run();
    return 0;
};


//
//    Music music_1 = Music("testId", "Mac Miller", 2020);
//
//    Song song_1 = Song(music_1, "Good News", "Rap", 5);
//    Song song_2 = Song(music_1, "Best Day Ever", "Rap", 2);
//    Song song_3 = Song(music_1, "Nikes on my Feet", "Rap", 4);
//    Song song_4 = Song(music_1, "Wings", "Rap", 4);
//
//    Playlist playlistTwo;
//
//    playlistTwo.insert_song(song_1);
//    playlistTwo.insert_song(song_2);
//    playlistTwo.insert_song(song_3);
//    playlistTwo.insert_song(song_4);
//
//    Playlist shuffled_playlist_test = playlistTwo.shuffle_songs();
//
//    playlistTwo.print();
//    shuffled_playlist_test.print();

