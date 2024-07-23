#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define NUM_RECORDS 200000  // Number of records to generate

#define MAX_NAME_LENGTH 30
#define MAX_EMAIL_LENGTH 50
#define MAX_CITY_LENGTH 30
#define MAX_PREFECTURE_LENGTH 20

typedef struct {
    char first_name[MAX_NAME_LENGTH + 1];
    char last_name[MAX_NAME_LENGTH + 1];
    int age;
    char email[MAX_EMAIL_LENGTH + 1];
    float height;
    char city[MAX_CITY_LENGTH + 1];
    char prefecture[MAX_PREFECTURE_LENGTH + 1];
} Person;


const char* prefectures[] = {
    "Hokkaido", "Aomori", "Iwate", "Miyagi", "Akita", "Yamagata", "Fukushima",
    "Ibaraki", "Tochigi", "Gunma", "Saitama", "Chiba", "Tokyo", "Kanagawa",
    "Niigata", "Toyama", "Ishikawa", "Fukui", "Yamanashi", "Nagano", "Gifu",
    "Shizuoka", "Aichi", "Mie", "Shiga", "Kyoto", "Osaka", "Hyogo", "Nara",
    "Wakayama", "Tottori", "Shimane", "Okayama", "Hiroshima", "Yamaguchi",
    "Tokushima", "Kagawa", "Ehime", "Kochi", "Fukuoka", "Saga", "Nagasaki",
    "Kumamoto", "Oita", "Miyazaki", "Kagoshima", "Okinawa"
};

// Arrays for random data generation
const char* first_names[] = {
    "Haruto", "Yua", "Sota", "Aoi", "Ren", "Himari", "Haru", "Ichika", "Akira", "Yui",
    "Taiga", "Mei", "Yuto", "Sakura", "Soma", "Koharu", "Yuki", "Akari", "Riku", "Yuna",
    "Kaito", "Hina", "Hayato", "Mio", "Hiroto", "Rin", "Kota", "Yume", "Sora", "Nanami",
    "Minato", "Saki", "Yamato", "Miyu", "Takumi", "Hana", "Haruki", "Ayaka", "Yusei", "Riko",
    "Koki", "Noa", "Sosuke", "Ayane", "Tatsuki", "Ruka", "Ryusei", "Kokona", "Kazuki", "Yuka"
};

const char* last_names[] = {
    "Sato", "Suzuki", "Takahashi", "Tanaka", "Watanabe", "Ito", "Yamamoto", "Nakamura", "Kobayashi", "Kato",
    "Yoshida", "Yamada", "Sasaki", "Yamaguchi", "Saito", "Matsumoto", "Inoue", "Kimura", "Hayashi", "Shimizu",
    "Yamazaki", "Mori", "Abe", "Ikeda", "Hashimoto", "Yamashita", "Ishikawa", "Nakajima", "Maeda", "Fujita",
    "Ogawa", "Goto", "Okada", "Hasegawa", "Murakami", "Kondo", "Ishii", "Saito", "Sakamoto", "Endo",
    "Aoki", "Fujii", "Nishimura", "Fukuda", "Ota", "Miura", "Fujiwara", "Okamoto", "Matsuda", "Nakagawa"
};

const char* cities[] = {
    "Tokyo", "Yokohama", "Osaka", "Nagoya", "Sapporo", "Fukuoka", "Kobe", "Kyoto", "Kawasaki", "Saitama",
    "Hiroshima", "Sendai", "Chiba", "Kitakyushu", "Sakai", "Niigata", "Hamamatsu", "Kumamoto", "Sagamihara", "Shizuoka",
    "Okayama", "Kanazawa", "Utsunomiya", "Matsuyama", "Oita", "Nagasaki", "Yokosuka", "Gifu", "Toyama", "Fukuyama",
    "Fujisawa", "Nara", "Takatsuki", "Iwaki", "Nagano", "Toyota", "Suita", "Takamatsu", "Koriyama", "Okazaki",
    "Kawagoe", "Tokorozawa", "Toyohashi", "Kochi", "Kashiwa", "Akita", "Miyazaki", "Koshigaya", "Naha", "Aomori"
};

Person generate_random_person() {
    Person p;
    strncpy(p.first_name, first_names[rand() % (sizeof(first_names) / sizeof(first_names[0]))], MAX_NAME_LENGTH);
    p.first_name[MAX_NAME_LENGTH] = '\0';

    strncpy(p.last_name, last_names[rand() % (sizeof(last_names) / sizeof(last_names[0]))], MAX_NAME_LENGTH);
    p.last_name[MAX_NAME_LENGTH] = '\0';

    p.age = rand() % 80 + 18;  // Age between 18 and 97

    snprintf(p.email, MAX_EMAIL_LENGTH + 1, "%s.%s@example.com", p.first_name, p.last_name);

    p.height = (rand() % 60 + 150) / 100.0f;  // Height between 1.50 and 2.10 meters

    strncpy(p.city, cities[rand() % (sizeof(cities) / sizeof(cities[0]))], MAX_CITY_LENGTH);
    p.city[MAX_CITY_LENGTH] = '\0';

    strncpy(p.prefecture, prefectures[rand() % (sizeof(prefectures) / sizeof(prefectures[0]))], MAX_PREFECTURE_LENGTH);
    p.prefecture[MAX_PREFECTURE_LENGTH] = '\0';

    return p;
}

void write_string(FILE* file, const char* str, int max_length) {
    uint8_t length = (uint8_t)strlen(str);
    fwrite(&length, sizeof(uint8_t), 1, file);
    fwrite(str, sizeof(char), length, file);
}

int main() {
    FILE* file = fopen("large_dataset_optimized.bin", "wb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    int num_records = NUM_RECORDS;
    fwrite(&num_records, sizeof(int), 1, file);

    for (int i = 0; i < NUM_RECORDS; i++) {
        Person person = generate_random_person();

        write_string(file, person.first_name, MAX_NAME_LENGTH);
        write_string(file, person.last_name, MAX_NAME_LENGTH);
        fwrite(&person.age, sizeof(int), 1, file);
        write_string(file, person.email, MAX_EMAIL_LENGTH);
        fwrite(&person.height, sizeof(float), 1, file);
        write_string(file, person.city, MAX_CITY_LENGTH);
        write_string(file, person.prefecture, MAX_PREFECTURE_LENGTH);
    }

    fclose(file);
    printf("Optimized binary dataset generated successfully.\n");

    return 0;
}