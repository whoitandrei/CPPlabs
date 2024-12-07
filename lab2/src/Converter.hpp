#pragma once
#include <string>
#include <random>
#include <limits>
#include "DATA.hpp"
#include "WAV.hpp"

// virtual class for fabric 
class Converter
{
private:
public:
    virtual void apply(WAV& wavFile) = 0;
    virtual ~Converter() = default;
};

class Mute final : public Converter{
private:
    DATA::COMMAND *cmd;
    size_t startSample;
    size_t endSample;
public:
    Mute(DATA::COMMAND *cmd);
    void apply(WAV& file);
    virtual ~Mute() = default;
};

class Mix final : public Converter{
private:
    DATA::COMMAND *cmd;
    std::string secondFilePath;
    size_t startSample;
    size_t endSample;
public:
    Mix(std::string secondFilePath, DATA::COMMAND *cmd);
    void apply(WAV& file);
    virtual ~Mix() = default;
};


class Random final : public Converter{
private:
    DATA::COMMAND *cmd;
    size_t startSample;
    size_t endSample;
public:
    Random(DATA::COMMAND *cmd);
    void apply(WAV& file);
    virtual ~Random() = default;
};