#include <cassert>
#include <iostream>

#define aboba std::cout << "aboba " << __LINE__ << std::endl;

enum CellStatus
{
    EMPTY,
    WIN,
    LOSS
};

enum SeekingLossCellsResult
{
    OK,
    LOSS_CELL_FOUND,
    LOSS_CELL_NOT_FOUND,
    ANSWER_DETERMINED
};


void DumpBoard(CellStatus **board, int X, int Y)
{
    assert(board != nullptr);

    for (int x = 0; x < X; ++x)
    {
        for (int y = 0; y < Y; ++y)
        {
            std::cout << board[x][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

bool CheckAllRightWin(CellStatus **board, int x_coord, int y_coord, int cols_quantity)
{
    assert(board != nullptr);

    bool if_all_win = true;

    ++y_coord;
    for (; y_coord < cols_quantity; ++y_coord)
    {
        if (board[x_coord][y_coord] != CellStatus::WIN)
        {
            if_all_win = false;

            break;
        }
    }

    return if_all_win;
}

bool CheckAllTopWin(CellStatus **board, int x_coord, int y_coord)
{
    assert(board != nullptr);

    bool if_all_win = true;

    --x_coord;
    for (; x_coord >= 0; --x_coord)
    {
        if (board[x_coord][y_coord] != CellStatus::WIN)
        {
            if_all_win = false;

            break;
        }
    }

    return if_all_win;
}

bool CheckAllDiagonWin(CellStatus **board, int x_coord, int y_coord, int cols_quantity)
{
    assert(board != nullptr);

    bool if_all_win = true;

    --x_coord;
    ++y_coord;
    for (; x_coord >= 0 && y_coord < cols_quantity; --x_coord, ++y_coord)
    {
        if (board[x_coord][y_coord] != CellStatus::WIN)
        {
            if_all_win = false;

            break;
        }
    }

    return if_all_win;
}

SeekingLossCellsResult IfMarkedNewLoss(CellStatus **board, int X, int Y, int &found_x_coord, int &found_y_coord)
{
    assert(board != nullptr);

    for (int x = 1; x < X; ++x)
    {
        for (int y = 0; y < Y - 1; ++y)
        {
            if ((board[x][y] == CellStatus::EMPTY) && (board[x - 1][y] == CellStatus::WIN) && (board[x][y + 1] == CellStatus::WIN))
            {
                bool if_loss = CheckAllRightWin(board, x, y, Y);
                if (!if_loss)
                {
                    continue;
                }
                if_loss = CheckAllTopWin(board, x, y);
                if (!if_loss)
                {
                    continue;
                }
                if_loss = CheckAllDiagonWin(board, x, y, Y);
                if (!if_loss)
                {
                    continue;
                }


                board[x][y] = CellStatus::LOSS;
                found_x_coord = x;
                found_y_coord = y;

                if ((x == X - 1) && (y == 0))
                {
                    return SeekingLossCellsResult::ANSWER_DETERMINED;
                }

                return SeekingLossCellsResult::LOSS_CELL_FOUND;
            }
        }
    }

    return SeekingLossCellsResult::LOSS_CELL_NOT_FOUND;
}

SeekingLossCellsResult MarkAllLeftWin(CellStatus **board, int x_coord, int y_coord, int rows_quantity)
{
    assert(board != nullptr);

    for (; y_coord >= 0; --y_coord)
    {
        if (board[x_coord][y_coord] == CellStatus::EMPTY)
        {
            board[x_coord][y_coord] = CellStatus::WIN;

            if ((x_coord == rows_quantity - 1) && (y_coord == 0))
            {
                return SeekingLossCellsResult::ANSWER_DETERMINED;
            }
        }
    }

    return SeekingLossCellsResult::OK;
}

SeekingLossCellsResult MarkAllBottomWin(CellStatus **board, int x_coord, int y_coord, int rows_quantity)
{
    assert(board != nullptr);

    for (; x_coord < rows_quantity; ++x_coord)
    {
        if (board[x_coord][y_coord] == CellStatus::EMPTY)
        {
            board[x_coord][y_coord] = CellStatus::WIN;

            if ((x_coord == rows_quantity - 1) && (y_coord == 0))
            {
                return SeekingLossCellsResult::ANSWER_DETERMINED;
            }
        }
    }

    return SeekingLossCellsResult::OK;
}

SeekingLossCellsResult MarkAllDiagonWin(CellStatus **board, int x_coord, int y_coord, int rows_quantity)
{
    assert(board != nullptr);

    for (; x_coord < rows_quantity && y_coord >= 0; ++x_coord, --y_coord)
    {
        if (board[x_coord][y_coord] == CellStatus::EMPTY)
        {
            board[x_coord][y_coord] = CellStatus::WIN;

            if ((x_coord == rows_quantity - 1) && (y_coord == 0))
            {
                return SeekingLossCellsResult::ANSWER_DETERMINED;
            }
        }
    }

    return SeekingLossCellsResult::OK;
}

int main()
{
    int X = 0;
    int Y = 0;
    std::cin >> X >> Y;
    CellStatus **board = new CellStatus *[X];
    for (int i = 0; i < X; ++i)
    {
        board[i] = new CellStatus[Y];
        for (int j = 0; j < Y; ++j)
        {
            board[i][j] = CellStatus::EMPTY;
        }
    }

    int loss_x_coord = 0;
    int loss_y_coord = Y - 1;
    board[loss_x_coord][loss_y_coord] = CellStatus::LOSS;
    MarkAllLeftWin  (board, loss_x_coord, loss_y_coord, X);
    MarkAllBottomWin(board, loss_x_coord, loss_y_coord, X);
    MarkAllDiagonWin(board, loss_x_coord, loss_y_coord, X); 
    for (; IfMarkedNewLoss(board, X, Y, loss_x_coord, loss_y_coord) == LOSS_CELL_FOUND;)
    {
        SeekingLossCellsResult result = SeekingLossCellsResult::OK;
        result = MarkAllLeftWin  (board, loss_x_coord, loss_y_coord, X);
        if (result == SeekingLossCellsResult::ANSWER_DETERMINED)
        {
            break;
        }
        result = MarkAllBottomWin(board, loss_x_coord, loss_y_coord, X);
        if (result == SeekingLossCellsResult::ANSWER_DETERMINED)
        {
            break;
        }
        result = MarkAllDiagonWin(board, loss_x_coord, loss_y_coord, X);
        if (result == SeekingLossCellsResult::ANSWER_DETERMINED)
        {
            break;
        }
    }

    if (board[X - 1][0] == CellStatus::LOSS)
    {
        std::cout << "S" << std::endl;
    }
    else
    {
        std::cout << "F" << std::endl;
    }

    for (int i = 0; i < X; ++i)
    {
        delete [] board[i];
    }
    delete [] board;

    return 0;
}