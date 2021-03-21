#include <cassert>
#include <stdexcept> // out_of_range
#include "gtest/gtest.h"
#include "circular_buffer.h"

TEST(CircularBufferTest, capacity) {
    circular_buffer<int, 32> buf1{};
    EXPECT_EQ(31, buf1.capacity());

    circular_buffer<int, 1> buf2{};
    EXPECT_EQ(0, buf2.capacity());
}

TEST(CircularBufferTest, full) {
    circular_buffer<int, 8> buf1{};
    EXPECT_EQ(false, buf1.full());
    for (int i = 0; i < 8; i++) {
        buf1.push_back(i);
    }
    EXPECT_EQ(true, buf1.full());

    circular_buffer<int, 1> buf2{};
    EXPECT_EQ(true, buf2.full());
}

TEST(CircularBufferTest, empty) {
    circular_buffer<int, 8> buf1{};
    EXPECT_EQ(true, buf1.empty());
    for (int i = 0; i < 8; i++) {
        buf1.push_back(i);
        EXPECT_EQ(false, buf1.empty());
    }

    circular_buffer<int, 1> buf2{};
    EXPECT_EQ(true, buf2.empty());
}

TEST(CircularBufferTest, len) {
    circular_buffer<int, 8> buf1{};
    EXPECT_EQ(0, buf1.len());
    for (int i = 1; i < 8; i++) {
        buf1.push_back(i);
        EXPECT_EQ(i, buf1.len());
    }
    // Push an element which will overwrite the oldest.
    buf1.push_back(8);
    EXPECT_EQ(7, buf1.len());

    circular_buffer<int, 1> buf2{};
    EXPECT_EQ(0, buf2.len());
    buf2.push_back(8);
    EXPECT_EQ(0, buf2.len());
}

TEST(CircularBufferTest, at) {
    circular_buffer<int, 8> buf{};
    const circular_buffer<int, 8>& cbuf = buf;

    for (int i = 0; i < 9; i++) {
        EXPECT_THROW(buf.at(i), std::out_of_range);
        EXPECT_THROW(cbuf.at(i), std::out_of_range);
    }

    buf.push_back(1);
    EXPECT_EQ(1, buf.at(0));
    EXPECT_EQ(1, cbuf.at(0));
    for (int i = 1; i < 9; i++) {
        EXPECT_THROW(buf.at(i), std::out_of_range);
        EXPECT_THROW(cbuf.at(i), std::out_of_range);
    }
}

TEST(CircularBufferTest, operator_array) {
    circular_buffer<int, 8> buf{};
    const circular_buffer<int, 8>& cbuf = buf;

    for (int i = 0; i < 9; i++) {
        EXPECT_NO_THROW(buf[i]);
        EXPECT_NO_THROW(cbuf[i]);
    }

    buf.push_back(1);
    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(1, cbuf[0]);
    for (int i = 1; i < 9; i++) {
        EXPECT_NO_THROW(buf[i]);
        EXPECT_NO_THROW(cbuf[i]);
    }
}

TEST(CircularBufferTest, back) {
    circular_buffer<int, 8> buf{};
    const circular_buffer<int, 8>& cbuf = buf;

    buf.push_back(1);
    EXPECT_EQ(1, buf.back());
    EXPECT_EQ(1, cbuf.back());
    buf.push_back(2);
    EXPECT_EQ(2, buf.back());
    EXPECT_EQ(2, cbuf.back());

    for (int i = 10; i < 18; i++) {
        buf.push_back(i);
    }
    EXPECT_EQ(17, buf.back());
    EXPECT_EQ(17, cbuf.back());
}

TEST(CircularBufferTest, front) {
    circular_buffer<int, 8> buf{};
    const circular_buffer<int, 8>& cbuf = buf;

    buf.push_back(1);
    EXPECT_EQ(1, buf.front());
    EXPECT_EQ(1, cbuf.front());
    buf.push_back(2);
    EXPECT_EQ(1, buf.front());
    EXPECT_EQ(1, cbuf.front());

    for (int i = 10; i < 18; i++) {
        buf.push_back(i);
    }
    EXPECT_EQ(11, buf.front());
    EXPECT_EQ(11, cbuf.front());
}

TEST(CircularBufferTest, push_back) {
    circular_buffer<std::pair<int, int>, 8> buf{};

    for (int i = 0; i < 20; i++) {
        auto p = std::make_pair(i, i);
        buf.push_back(p);
        EXPECT_EQ(p, buf.back());
        EXPECT_NE(&p, &buf.back());
    }

    for (int i = 0; i < 20; i++) {
        auto p = std::make_pair(i, i);
        buf.push_back(std::move(p));
        EXPECT_EQ(i, buf.back().first);
        EXPECT_EQ(i, buf.back().second);
    }
}

TEST(CircularBufferTest, pop_back) {
    circular_buffer<int, 8> buf{};

    buf.push_back(1);
    buf.push_back(2);
    EXPECT_EQ(2, buf.len());
    EXPECT_EQ(1, buf.front());
    EXPECT_EQ(2, buf.back());

    buf.pop_back();
    EXPECT_EQ(1, buf.len());
    EXPECT_EQ(1, buf.front());
    EXPECT_EQ(1, buf.back());

    for (int i = 10; i < 18; i++) {
        buf.push_back(i);
    }
    EXPECT_EQ(7, buf.len());
    EXPECT_EQ(11, buf.front());
    EXPECT_EQ(17, buf.back());

    buf.pop_back();
    EXPECT_EQ(6, buf.len());
    EXPECT_EQ(11, buf.front());
    EXPECT_EQ(16, buf.back());
}

TEST(CircularBufferTest, pop_front) {
    circular_buffer<int, 8> buf{};

    buf.push_back(1);
    buf.push_back(2);
    EXPECT_EQ(2, buf.len());
    EXPECT_EQ(1, buf.front());
    EXPECT_EQ(2, buf.back());

    buf.pop_front();
    EXPECT_EQ(1, buf.len());
    EXPECT_EQ(2, buf.front());
    EXPECT_EQ(2, buf.back());

    for (int i = 10; i < 18; i++) {
        buf.push_back(i);
    }
    EXPECT_EQ(7, buf.len());
    EXPECT_EQ(11, buf.front());
    EXPECT_EQ(17, buf.back());

    buf.pop_front();
    EXPECT_EQ(6, buf.len());
    EXPECT_EQ(12, buf.front());
    EXPECT_EQ(17, buf.back());
}

TEST(CircularBufferTest, iterators) {
    circular_buffer<int, 8> buf{};
    const circular_buffer<int, 8>& cbuf = buf;
    const std::array<int, 8> expected {0, 1, 2, 3, 4, 5, 6, 7};
    int expected_index = 0;

    // First a simple iteration - buf is under capacity so tail is behind head.
    for (int i = 0; i < 4; i++) {
        buf.push_back(i);
    }
    expected_index = 0;
    for (int i : buf) {
        ASSERT_LT(expected_index, 4);
        EXPECT_EQ(expected[expected_index++], i);
    }
    EXPECT_EQ(4, expected_index);
    expected_index = 0;
    for (int i : cbuf) {
        ASSERT_LT(expected_index, 7);
        EXPECT_EQ(expected[expected_index++], i);
    }
    EXPECT_EQ(4, expected_index);

    // Next a more devious example - overflow the buffer so that tail ends up
    // in front of head.
    for (int i = 4; i < 8; i++) {
        buf.push_back(i);
    }
    expected_index = 1;
    for (int i : buf) {
        ASSERT_LT(expected_index, 8);
        EXPECT_EQ(expected[expected_index++], i);
    }
    EXPECT_EQ(8, expected_index);

    expected_index = 1;
    for (int i : cbuf) {
        ASSERT_LT(expected_index, 8);
        EXPECT_EQ(expected[expected_index++], i);
    }
    EXPECT_EQ(8, expected_index);
}

TEST(CircularBufferTest, list_initialization) {
    circular_buffer<int, 8> buf {1, 2, 3};
    EXPECT_EQ(7, buf.capacity());
    EXPECT_EQ(3, buf.len());
    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);
    buf.push_back(4);
    EXPECT_EQ(4, buf.len());
    EXPECT_EQ(4, buf[3]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}