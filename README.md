[![main](https://github.com/flowerinthenight/clockbound-ffi-go/actions/workflows/main.yml/badge.svg)](https://github.com/flowerinthenight/clockbound-ffi-go/actions/workflows/main.yml)
[![Go Reference](https://pkg.go.dev/badge/github.com/flowerinthenight/clockbound-ffi-go.svg)](https://pkg.go.dev/github.com/flowerinthenight/clockbound-ffi-go)

## clockbound-ffi-go

A Go client for [AWS ClockBound](https://github.com/aws/clock-bound) using the provided [FFI](https://github.com/aws/clock-bound/tree/main/clock-bound-ffi) (requires [CGO](https://pkg.go.dev/cmd/cgo)).

The [ClockBound daemon](https://github.com/aws/clock-bound/tree/main/clock-bound-d) must be running in order to use this library, as well as the dependencies from the FFI.

```sh
# Rust environment is expected to be installed.
$ git clone https://github.com/aws/clock-bound
$ cd clock-bound/clock-bound-ffi/
$ cargo build --release
$ cd ../
$ [sudo] cp clock-bound-ffi/include/clockbound.h /usr/include/
$ [sudo] cp target/release/libclockbound.a /usr/lib/
$ [sudo] cp target/release/libclockbound.so /usr/lib/
```

Usage looks something like this (you need to have a C compiler for `CGO`):

```go
import (
  ...
  "github.com/flowerinthenight/clockbound-ffi-go"
)

func main() {
  // error checks redacted
  client, _ := clockbound.New()
  now, _ := client.Now()
  ...
  client.Close()
}
```

Check out the provided [example](./example/main.go) code for a more complete reference on how to use the client.

## License

This library is licensed under the [MIT License](./LICENSE).
