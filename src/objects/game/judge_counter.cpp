#include "../../libs/texture.h"
#include "judge_counter.h"
#include <cmath>


JudgeCounter::JudgeCounter()
    : good(0), ok(0), bad(0), drumrolls(0) {
    orange = ray::Color{253, 161, 0, 255};
    white = ray::WHITE;
}

void JudgeCounter::update(int good, int ok, int bad, int drumrolls) {
    this->good = good;
    this->ok = ok;
    this->bad = bad;
    this->drumrolls = drumrolls;
}

void JudgeCounter::draw_counter(float counter, float x, float y, float margin, ray::Color color) {
    std::string counter_str = std::to_string((int)std::round(counter));
    int counter_len = counter_str.length();

    for (int i = 0; i < counter_str.length(); i++) {
        tex.draw_texture(JUDGE_COUNTER::COUNTER, {
            .color = color,
            .frame = counter_str[i] - '0',
            .x = x - (counter_len - i) * margin,
            .y = y
        });
    }
}

void JudgeCounter::draw() {
    tex.draw_texture(JUDGE_COUNTER::BG);
    tex.draw_texture(JUDGE_COUNTER::TOTAL_PERCENT);
    tex.draw_texture(JUDGE_COUNTER::JUDGMENTS);
    tex.draw_texture(JUDGE_COUNTER::DRUMROLLS);

    for (int i = 0; i < 4; i++) {
        tex.draw_texture(JUDGE_COUNTER::PERCENT, {
            .color = orange,
            .index = i
        });
    }

    int total_notes = good + ok + bad;
    if (total_notes == 0) {
        total_notes = 1;
    }

    float margin = tex.skin_config[SC::JUDGE_COUNTER_MARGIN].x;

    draw_counter(good / (float)total_notes * 100, // SC::JUDGE_COUNTER_DRAW_TOTAL_NOTES_GOOD
                 260,
                 360,
                 margin, orange);

    draw_counter(ok / (float)total_notes * 100, // SC::JUDGE_COUNTER_DRAW_TOTAL_NOTES_OK
                 353 + 260,
                 360,
                 margin, orange);

    draw_counter(bad / (float)total_notes * 100, // SC::JUDGE_COUNTER_DRAW_TOTAL_NOTES_BAD
                 706 + 260,
                 360,
                 margin, orange);

    draw_counter((good + ok) / (float)total_notes * 100, // SC::JUDGE_COUNTER_DRAW_TOTAL_NOTES_GOOD_AND_OK
                 -4096,
                 -4096,
                 margin, orange);

    draw_counter(good, // SC::JUDGE_COUNTER_DRAW_GOOD
                 180,
                 360,
                 margin, white);

    draw_counter(ok, // SC::JUDGE_COUNTER_DRAW_OK
                 353 + 180,
                 360,
                 margin, white);

    draw_counter(bad, // SC::JUDGE_COUNTER_DRAW_BAD
                 706 + 180,
                 360,
                 margin, white);

    draw_counter(drumrolls, // SC::JUDGE_COUNTER_DRAW_DRUMROLLS
                 1060 + 180,
                 360,
                 margin, white);
}