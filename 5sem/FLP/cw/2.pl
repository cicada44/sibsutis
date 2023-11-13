% Предикат для чтения строк из потока
read_lines(Stream, [Line | Lines]) :-
    read_line_to_string(Stream, Line),
    Line \= end_of_file,
    read_lines(Stream, Lines).
read_lines(_, []).

% Предикат для записи списка слов в файл
write_words_to_file(File, Words) :-
    open(File, write, Stream),
    write_words(Stream, Words),
    close(Stream).

write_words(_, []).
write_words(Stream, [Word | Words]) :-
    write(Stream, Word),
    write(Stream, ' '),
    write_words(Stream, Words).

% Предикат для подсчета количества гласных букв в слове
count_vowels(Word, Count) :-
    atom_chars(Word, Chars),
    include(vowel, Chars, Vowels),
    length(Vowels, Count).

% Предикат для определения, является ли символ гласной буквой
vowel(Char) :-
    member(Char, [a, e, i, o, u]).

% Предикат для чтения строк из файла и нахождения слов с наибольшим числом гласных
find_words_with_max_vowels(File, Words) :-
    open(File, read, Stream),
    read_lines(Stream, Lines),
    close(Stream),
    findall(Word, (member(Line, Lines), split_string(Line, " ", "", Words), member(Word, Words), count_vowels(Word, Count), Count > 0), WordsWithVowels),
    max_vowel_count(WordsWithVowels, MaxCount),
    findall(Word, (member(Word, WordsWithVowels), count_vowels(Word, MaxCount)), Words),
    write_words_to_file('output.txt', Words).

% Предикат для нахождения максимального числа гласных в списке слов
max_vowel_count(Words, MaxCount) :-
    maplist(count_vowels, Words, Counts),
    max_list(Counts, MaxCount).