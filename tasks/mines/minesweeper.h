#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    std::vector<int> min_inside_;
    std::vector<int> field_now_;
    GameStatus gamestatus_ = GameStatus::NOT_STARTED;
    size_t fwidth_ = 0;
    size_t fheight_ = 0;
    size_t prizenumber_ = 0;
    void Initialize(size_t width, size_t height, size_t mines_count);
    void Initialize(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);
    int MinesCounter(size_t i);
    bool clicked_ = false;
    time_t start_;
    time_t over_;
    std::unordered_set<size_t> were_in_bfs_;
};
