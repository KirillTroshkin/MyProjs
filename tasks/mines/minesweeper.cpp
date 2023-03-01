#include "minesweeper.h"
#include <ctime>
#include <iostream>
#include <queue>
#include <random>

int Minesweeper::MinesCounter(size_t i) {
    int mines_counter = 0;
    if (i / fwidth_ == 0) {
        if (i % fwidth_ == 0) {
            if (fwidth_ != 1 && min_inside_[i + 1] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && min_inside_[i + fwidth_] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ + 1] == '*') {
                ++mines_counter;
            }
            return mines_counter;
        }
        if (i % fwidth_ == (fwidth_ - 1)) {
            if (fwidth_ != 1 && min_inside_[i - 1] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && min_inside_[i + fwidth_] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ - 1] == '*') {
                ++mines_counter;
            }
            return mines_counter;
        }
        if (fwidth_ != 1 && min_inside_[i - 1] == '*') {
            ++mines_counter;
        }
        if (fwidth_ != 1 && min_inside_[i + 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && min_inside_[i + fwidth_] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ + 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ - 1] == '*') {
            ++mines_counter;
        }
        return mines_counter;
    }
    if (i / fwidth_ == (fheight_ - 1)) {
        if (i % fwidth_ == 0) {
            if (fwidth_ != 1 && min_inside_[i + 1] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && min_inside_[i - fwidth_] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ + 1] == '*') {
                ++mines_counter;
            }
            return mines_counter;
        }
        if (i % fwidth_ == (fwidth_ - 1)) {
            if (fwidth_ != 1 && min_inside_[i - 1] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && min_inside_[i - fwidth_] == '*') {
                ++mines_counter;
            }
            if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ - 1] == '*') {
                ++mines_counter;
            }
            return mines_counter;
        }
        if (fwidth_ != 1 && min_inside_[i - 1] == '*') {
            ++mines_counter;
        }
        if (fwidth_ != 1 && min_inside_[i + 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && min_inside_[i - fwidth_] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ - 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ + 1] == '*') {
            ++mines_counter;
        }
        return mines_counter;
    }
    if (i % fwidth_ == 0) {
        if (fwidth_ != 1 && min_inside_[i + 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && min_inside_[i - fwidth_] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && min_inside_[i + fwidth_] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ + 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ + 1] == '*') {
            ++mines_counter;
        }
        return mines_counter;
    }
    if (i % fwidth_ == (fwidth_ - 1)) {
        if (fwidth_ != 1 && min_inside_[i - 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && min_inside_[i - fwidth_] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && min_inside_[i + fwidth_] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ - 1] == '*') {
            ++mines_counter;
        }
        if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ - 1] == '*') {
            ++mines_counter;
        }
        return mines_counter;
    }
    if (fwidth_ != 1 && min_inside_[i - 1] == '*') {
        ++mines_counter;
    }
    if (fwidth_ != 1 && min_inside_[i + 1] == '*') {
        ++mines_counter;
    }
    if (fheight_ != 1 && min_inside_[i - fwidth_] == '*') {
        ++mines_counter;
    }
    if (fheight_ != 1 && min_inside_[i + fwidth_] == '*') {
        ++mines_counter;
    }
    if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ + 1] == '*') {
        ++mines_counter;
    }
    if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i + fwidth_ - 1] == '*') {
        ++mines_counter;
    }
    if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ + 1] == '*') {
        ++mines_counter;
    }
    if (fheight_ != 1 && fwidth_ != 1 && min_inside_[i - fwidth_ - 1] == '*') {
        ++mines_counter;
    }
    return mines_counter;
}

void Minesweeper::Initialize(size_t width, size_t height, size_t mines_count) {
    fwidth_ = width;
    fheight_ = height;
    prizenumber_ = fwidth_ * fheight_ - mines_count;
    std::vector<size_t> default_numbers;
    for (size_t i = 0; i < width * height; ++i) {
        field_now_.emplace_back('-');
        min_inside_.emplace_back('.');
        default_numbers.emplace_back(i);
    }
    shuffle(default_numbers.begin(), default_numbers.end(), std::mt19937(std::random_device()()));
    for (size_t i = 0; i < mines_count; ++i) {
        min_inside_[default_numbers[i]] = '*';
    }
    for (size_t i = 0; i < min_inside_.size(); ++i) {
        if (min_inside_[i] != '*') {
            if (MinesCounter(i) != 0) {
                min_inside_[i] = static_cast<char>('0' + MinesCounter(i));
            }
        }
    }
    gamestatus_ = GameStatus::IN_PROGRESS;
}

void Minesweeper::Initialize(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    fwidth_ = width;
    fheight_ = height;
    prizenumber_ = fwidth_ * fheight_ - cells_with_mines.size();
    for (size_t i = 0; i < width * height; ++i) {
        field_now_.emplace_back('-');
        min_inside_.emplace_back('.');
    }
    for (auto cell : cells_with_mines) {
        min_inside_[cell.y * width + cell.x] = '*';
    }
    for (size_t i = 0; i < min_inside_.size(); ++i) {
        if (min_inside_[i] != '*') {
            if (MinesCounter(i) != 0) {
                min_inside_[i] = static_cast<char>('0' + MinesCounter(i));
            }
        }
    }
    gamestatus_ = GameStatus::IN_PROGRESS;
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    Initialize(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    Initialize(width, height, cells_with_mines);
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    min_inside_.clear();
    field_now_.clear();
    Initialize(width, height, mines_count);
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    min_inside_.clear();
    field_now_.clear();
    Initialize(width, height, cells_with_mines);
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (!clicked_) {
        start_ = std::time(nullptr);
    }
    clicked_ = true;
    if (gamestatus_ != GameStatus::DEFEAT && gamestatus_ != GameStatus::VICTORY &&
        field_now_[cell.y * fwidth_ + cell.x] != '?') {
        if (min_inside_[cell.y * fwidth_ + cell.x] == '*') {
            for (size_t i = 0; i < min_inside_.size(); ++i) {
                field_now_[i] = min_inside_[i];
            }
            over_ = std::time(nullptr);
            gamestatus_ = GameStatus::DEFEAT;
        } else {
            std::queue<size_t> bfs;
            bfs.push(cell.y * fwidth_ + cell.x);
            while (!bfs.empty()) {
                field_now_[bfs.front()] = min_inside_[bfs.front()];
                were_in_bfs_.insert(bfs.front());
                if (MinesCounter(bfs.front()) == 0) {
                    if (fheight_ > 1 && bfs.front() / fwidth_ != 0 &&
                        were_in_bfs_.find(bfs.front() - fwidth_) == were_in_bfs_.end() &&
                        field_now_[bfs.front() - fwidth_] != '?') {
                        bfs.push(bfs.front() - fwidth_);
                    }
                    if (fheight_ > 1 && bfs.front() / fwidth_ != (fheight_ - 1) &&
                        were_in_bfs_.find(bfs.front() + fwidth_) == were_in_bfs_.end() &&
                        field_now_[bfs.front() + fwidth_] != '?') {
                        bfs.push(bfs.front() + fwidth_);
                    }
                    if (fwidth_ > 1 && bfs.front() % fwidth_ != 0 &&
                        were_in_bfs_.find(bfs.front() - 1) == were_in_bfs_.end() &&
                        field_now_[bfs.front() - 1] != '?') {
                        bfs.push(bfs.front() - 1);
                    }
                    if (fwidth_ > 1 && bfs.front() % fwidth_ != (fwidth_ - 1) &&
                        were_in_bfs_.find(bfs.front() + 1) == were_in_bfs_.end() &&
                        field_now_[bfs.front() + 1] != '?') {
                        bfs.push(bfs.front() + 1);
                    }
                    if (fheight_ > 1 && fwidth_ > 1 && bfs.front() / fwidth_ != 0 && bfs.front() % fwidth_ != 0 &&
                        were_in_bfs_.find(bfs.front() - fwidth_ - 1) == were_in_bfs_.end() &&
                        field_now_[bfs.front() - fwidth_ - 1] != '?') {
                        bfs.push(bfs.front() - fwidth_ - 1);
                    }
                    if (fheight_ > 1 && fwidth_ > 1 && bfs.front() / fwidth_ != 0 &&
                        bfs.front() % fwidth_ != (fwidth_ - 1) &&
                        were_in_bfs_.find(bfs.front() - fwidth_ + 1) == were_in_bfs_.end() &&
                        field_now_[bfs.front() - fwidth_ + 1] != '?') {
                        bfs.push(bfs.front() - fwidth_ + 1);
                    }
                    if (fheight_ > 1 && fwidth_ > 1 && bfs.front() / fwidth_ != (fheight_ - 1) &&
                        bfs.front() % fwidth_ != (fwidth_ - 1) &&
                        were_in_bfs_.find(bfs.front() + fwidth_ + 1) == were_in_bfs_.end() &&
                        field_now_[bfs.front() + fwidth_ + 1] != '?') {
                        bfs.push(bfs.front() + fwidth_ + 1);
                    }
                    if (fheight_ > 1 && fwidth_ > 1 && bfs.front() / fwidth_ != (fheight_ - 1) &&
                        bfs.front() % fwidth_ != 0 &&
                        were_in_bfs_.find(bfs.front() + fwidth_ - 1) == were_in_bfs_.end() &&
                        field_now_[bfs.front() + fwidth_ - 1] != '?') {
                        bfs.push(bfs.front() + fwidth_ - 1);
                    }
                }
                bfs.pop();
            }
            if (were_in_bfs_.size() == prizenumber_) {
                over_ = std::time(nullptr);
                gamestatus_ = GameStatus::VICTORY;
            }
        }
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (!clicked_) {
        start_ = std::time(nullptr);
    }
    clicked_ = true;
    if (gamestatus_ != GameStatus::DEFEAT && gamestatus_ != GameStatus::VICTORY) {
        if (field_now_[cell.y * fwidth_ + cell.x] == '?') {
            field_now_[cell.y * fwidth_ + cell.x] = '-';
        } else {
            field_now_[cell.y * fwidth_ + cell.x] = '?';
        }
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return gamestatus_;
}

time_t Minesweeper::GetGameTime() const {
    if (gamestatus_ == GameStatus::VICTORY || gamestatus_ == GameStatus::DEFEAT) {
        return over_ - start_;
    }
    return std::time(nullptr) - start_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    std::vector<std::string> field;
    for (size_t i = 0; i < fheight_; ++i) {
        std::string line;
        for (size_t j = 0; j < fwidth_; ++j) {
            line += field_now_[i * fwidth_ + j];
        }
        field.emplace_back(line);
    }
    return field;
}
