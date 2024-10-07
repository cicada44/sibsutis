#include "../include/pokerlib.h"

void print_card(char *name, char *suit) {
    if (!strcmp(name, "jack")) {
        printf("%sJ%s ", WHITE, RESET);
    } else if (!strcmp(name, "queen")) {
        printf("%sQ%s ", WHITE, RESET);
    } else if (!strcmp(name, "king")) {
        printf("%sK%s ", WHITE, RESET);
    } else if (!strcmp(name, "ace")) {
        printf("%sA%s ", WHITE, RESET);
    } else
        printf("%s%s%s ", WHITE, name, RESET);
    if (!strcmp(suit, "clubs")) {
        printf("%s\n", CLUB);
    } else if (!strcmp(suit, "spades")) {
        printf("%s\n", SPADE);
    } else if (!strcmp(suit, "diamonds")) {
        printf("%s\n", DIAMOND);
    } else if (!strcmp(suit, "hearts")) {
        printf("%s\n", HEART);
    }
}

void swap_card(unsigned long int *card_a, unsigned long int *card_b) {
    unsigned long int tmp;
    tmp = *card_a;
    *card_a = *card_b;
    *card_b = tmp;
}

void mental_poker(int n_players) {
    if (n_players < 3 && n_players > 1)
        printf("%s[S]%s\tAmount of players are less than 3. Debug is ON\n", YELLOW, RESET);
    else if (n_players > 23) {
        fprintf(stderr, "%s[E]%s Wrong amount of players\n", RED, RESET);
        exit(EXIT_FAILURE);
    } else if (n_players <= 1) {
        fprintf(stderr, "%s[E]%s There must be 2+ players!\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    // Not a Cophie
    unsigned long int general_p;
    generate_prime_number(1000, MAXINT, &general_p);
    if (n_players < 3) printf("%s[D]%s\tGeneral P was generated:\t%lu\n", BLUE, RESET, general_p);

    // C, D for each player
    unsigned long int c[n_players], d[n_players], euclid_res[3];
    for (int i = 0; i < n_players; ++i) {
        do {
            c[i] = generate_mutually_prime_number(general_p - 1, 1, general_p - 1);
            euclid(general_p - 1, c[i], euclid_res);
            d[i] = euclid_res[1];
        } while (d[i] > 0xFFFFFF);

        if (n_players < 3) printf("%s[D]%s\tFor Player %d generated:\t%lu\t%lu\n", BLUE, RESET, i, c[i], d[i]);
    }

    FILE *deck_file = fopen("deck", "r");
    if (deck_file == NULL) {
        fprintf(stderr, "%s[E]%s\tFile doesn't exist!\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    struct deck game_deck[NUMBER_CARDS];
    unsigned long int encoded_deck[NUMBER_CARDS];
    for (int i = 0; i < NUMBER_CARDS; ++i) {
        fscanf(deck_file, "%s", game_deck[i].suit);
        fscanf(deck_file, "%s", game_deck[i].name);
        game_deck[i].start_card = i + 1;
        encoded_deck[i] = i + 1;
    }
    fclose(deck_file);

    for (int i = 0; i < n_players; ++i) {
        for (int j = 0; j < NUMBER_CARDS; ++j) expmod_func(encoded_deck[j], c[i], general_p, &encoded_deck[j]);
        for (int j = 0; j < NUMBER_CARDS; ++j) swap_card(&encoded_deck[j], &encoded_deck[rand() % NUMBER_CARDS]);
    }

    unsigned long int curr_card = NUMBER_CARDS;
    struct deck player_hand[n_players][2];
    for (int i = 0; i < n_players; ++i) {
        int rand_card;
        for (int j = 0; j < 2; j++) {
            rand_card = rand() % curr_card;
            for (int k = 0; k < n_players; k++)
                if (i != k) expmod_func(encoded_deck[rand_card], d[k], general_p, &encoded_deck[rand_card]);
            expmod_func(encoded_deck[rand_card], d[i], general_p, &encoded_deck[rand_card]);
            for (int k = 0; k < NUMBER_CARDS; k++) {
                if (game_deck[k].start_card == encoded_deck[rand_card]) {
                    player_hand[i][j] = game_deck[k];
                    encoded_deck[rand_card] = encoded_deck[curr_card - 1];
                    curr_card--;
                    k = NUMBER_CARDS;
                }
            }
        }
        for (int j = 0; j < curr_card; j++) {
            rand_card = rand() % curr_card;
            swap_card(&encoded_deck[j], &encoded_deck[rand_card]);
        }
    }

    printf("\n%s[SYSTEM]%s %sCards on the board:%s\n", YELLOW, RESET, WHITE, RESET);
    for (int j = 0, rand_card; j < 5; j++) {
        rand_card = rand() % curr_card;
        for (int k = 0; k < n_players; k++) {
            expmod_func(encoded_deck[rand_card], d[k], general_p, &encoded_deck[rand_card]);
        }
        for (int k = 0; k < NUMBER_CARDS; k++) {
            if (game_deck[k].start_card == encoded_deck[rand_card]) {
                print_card(game_deck[k].name, game_deck[k].suit);
                encoded_deck[rand_card] = encoded_deck[curr_card - 1];
                curr_card--;
                k = NUMBER_CARDS;
            }
        }
    }

    printf("\n");
    for (int i = 0; i < n_players; i++) {
        printf("%s[SYSTEM]%s %sPlayer %d:%s\n", YELLOW, RESET, WHITE, i + 1, RESET);
        print_card(player_hand[i][0].name, player_hand[i][0].suit);
        print_card(player_hand[i][1].name, player_hand[i][1].suit);
        printf("\n");
    }
    printf("%s[SYSTEM]%s %sWidow: %lu cards%s\n", YELLOW, RESET, WHITE, curr_card, RESET);
}
