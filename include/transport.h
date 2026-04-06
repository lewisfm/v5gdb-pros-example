#pragma once

#include "v5gdb.h"
#include "api.h"
#include "pros/serial.hpp"
#include <cstring>


class SmartPortTransport : public v5gdb::Transport {
public:
    explicit SmartPortTransport(pros::Serial&& serial) : serial(serial) {}

    std::expected<std::monostate, char const *>
    write(std::span<uint8_t const> buffer) noexcept override;

    std::expected<std::monostate, char const*> flush() noexcept override;

    void initialize() noexcept override;

    std::expected<std::uint8_t, char const*> peek() noexcept override;

    std::expected<std::uint8_t, char const*> read() noexcept override;

private:
    pros::Serial serial;
};

std::expected<std::monostate, char const *> SmartPortTransport::write(
    std::span<uint8_t const> buffer
) noexcept {
    auto data = const_cast<uint8_t *>(buffer.data());
    int written = serial.write(data, buffer.size());
    if (written == PROS_ERR) {
        return std::unexpected(strerror(errno));
    }
    if (written != buffer.size()) {
        return std::unexpected("not all bytes were written");
    }
    return std::monostate {};
}
