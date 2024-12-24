#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdbool.h>

#define MOD 56800235584ULL
#define MULTIPLIER 31ULL

// Fonction de hashage
unsigned long long f_hashage(char *input)
{
    unsigned long long hash = 0;
    int i = 0;
    while (input[i] != '\0')
    {
        hash = (hash * MULTIPLIER + input[i]) % MOD;
        i++;
    }
    return hash;
}

// Conversion en Base62
void To_Base62(unsigned long long hash, char *output)
{
    const char alphabets[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    strcpy(output, "000000"); // Initialisation de output
    int i = -1;
    do
    {
        i++;
        output[i] = alphabets[hash % 62];
        hash /= 62;
    } while (hash > 0);
    output[i + 1] = '\0'; // Assure la terminaison de la chaîne
}

// Fonction de génération du code (encode)
void encode(char *input, char *output)
{
    unsigned long long hash = f_hashage(input);
    char output_inter[7];
    To_Base62(hash, output_inter);
    sprintf(output, "%s", output_inter);
}

// Fonction de vérification de l'existence du long_url dans la base
int check_url_in_db(sqlite3 *db, const char *long_url, int *num, char *code)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT num, code FROM urls WHERE long_url = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        printf("Erreur de préparation de la requête : %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, long_url, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        *num = sqlite3_column_int(stmt, 0);
        strcpy(code, (const char *)sqlite3_column_text(stmt, 1));
        sqlite3_finalize(stmt);
        return 1; // URL trouvée
    }

    sqlite3_finalize(stmt);
    return 0; // URL non trouvée
}

// Fonction pour insérer un nouveau couple (num, code, long_url)
int insert_url(sqlite3 *db, int num, const char *code, const char *long_url)
{
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO urls (num, code, long_url) VALUES (?, ?, ?)";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        printf("Erreur de préparation de la requête : %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_int(stmt, 1, num);
    sqlite3_bind_text(stmt, 2, code, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, long_url, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("Erreur lors de l'insertion : %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return 1; // Insertion réussie
}

// Fonction pour obtenir le maximum de `num` pour un `code` donné
int get_max_num_for_code(sqlite3 *db, const char *code)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT MAX(num) FROM urls WHERE code = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        printf("Erreur de préparation de la requête : %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, code, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        int max_num = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return max_num;
    }

    sqlite3_finalize(stmt);
    return 0; // Aucun code trouvé
}

// Fonction de décodage : "num-code" -> long_url
int decode(sqlite3 *db, const char *short_url, char *long_url)
{
    int num;
    char code[7];
    sscanf(short_url, "%d-%s", &num, code);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT long_url FROM urls WHERE num = ? AND code = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        printf("Erreur de préparation de la requête : %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_int(stmt, 1, num);
    sqlite3_bind_text(stmt, 2, code, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        strcpy(long_url, (const char *)sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
        return 1; // Long URL trouvé
    }

    sqlite3_finalize(stmt);
    return 0; // Long URL non trouvé
}

int main(int argc, char *argv[])
{
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Vérifier les arguments passés
    if (argc < 2)
    {
        printf("Usage: %s <option> [paramètres]\n", argv[0]);
        printf("Options:\n");
        printf("  encode <long_url>    : Générer un short_url\n");
        printf("  decode <short_url>   : Décoder un short_url\n");
        return 1;
    }

    // Ouvrir la base de données
    rc = sqlite3_open("short.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (strcmp(argv[1], "encode") == 0)
    {
        if (argc < 3)
        {
            printf("Veuillez fournir un long_url à encoder.\n");
            sqlite3_close(db);
            return 1;
        }

        char *long_url = argv[2];
        int num;
        char code[7];

        // Vérifier si le long_url est déjà dans la base de données
        if (check_url_in_db(db, long_url, &num, code))
        {
            printf("short url correspond = %d-%s\n", num, code);
        }
        else
        {
            // URL non trouvée, générer un code
            encode(long_url, code);

            // Vérifier si le code existe déjà dans la base
            int max_num = get_max_num_for_code(db, code);
            if (max_num >= 0)
            {
                num = max_num + 1; // Incrémenter le num pour ce code
            }
            else
            {
                num = 1; // Premier numéro pour ce code
            }

            // Insérer le nouveau couple (num, code, long_url) dans la base
            if (insert_url(db, num, code, long_url))
            {
                printf("short url correspond = %d-%s\n", num, code);
            }
            else
            {
                printf("Erreur lors de l'insertion.\n");
            }
        }
    }
    else if (strcmp(argv[1], "decode") == 0)
    {
        if (argc < 3)
        {
            printf("Veuillez fournir un short_url à décoder.\n");
            sqlite3_close(db);
            return 1;
        }

        char *short_url = argv[2];
        char decoded_url[256];

        if (decode(db, short_url, decoded_url))
        {
            printf("long url correspond = %s\n", decoded_url);
        }
        else
        {
            printf("long_url n'est pas trouvé\n");
        }
    }
    else
    {
        printf("Option invalide. Utilisez 'encode' ou 'decode'.\n");
    }

    // Fermer la base de données
    sqlite3_close(db);

    return 0;
}
