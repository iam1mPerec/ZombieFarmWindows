#pragma once

class farmer
{
    bool business;
public:
    
    farmer();

    void busy();
    void free();
    bool getbusiness() const;
    farmer* fellow;
};