struct listnode {
    char* key;
    int value;

    struct listnode* next;
};

unsigned int KRHash(char *s);
void hashtabInit(struct listnode** hashtab);
void hashtabAdd(struct listnode** hashtab, char* key, int value);
struct listnode* hashtabLookup(struct listnode** hashtab, char* key);
void hashtabDelete(struct listnode** hashtab, char* key);