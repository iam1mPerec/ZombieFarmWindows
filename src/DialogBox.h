#pragma once

class dialogBox
{
private:
    int py;
    int px;
    int NumberOfLines;

    char** Box;

    void lineDown(int line);

public:
    dialogBox();
    void AddQuote(const char* quote);
    void AddQuote(const std::string& quote);
    void clearBox();
    int getPy() const;
    int getPx() const;
    char** getBox() const;
};