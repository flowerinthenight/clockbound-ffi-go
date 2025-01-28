[![main](https://github.com/flowerinthenight/clockbound-ffi-go/actions/workflows/main.yml/badge.svg)](https://github.com/flowerinthenight/clockbound-ffi-go/actions/workflows/main.yml)

## clockbound-ffi-go

A Go client for [AWS ClockBound](https://github.com/aws/clock-bound) using the provided [FFI](https://github.com/aws/clock-bound/tree/main/clock-bound-ffi) (requires [CGO](https://pkg.go.dev/cmd/cgo)).

The [ClockBound daemon](https://github.com/aws/clock-bound/tree/main/clock-bound-d) must be running in order to use this library, as well as the dependencies from the FFI.

```sh
# Rust is expected to be installed.
$ git clone https://github.com/aws/clock-bound
$ cd clock-bound/clock-bound-ffi/
$ cargo build --release

$ cd ../
$ [sudo] cp clock-bound-ffi/include/clockbound.h /usr/include/
$ [sudo] cp target/release/libclockbound.so /usr/lib/
```
