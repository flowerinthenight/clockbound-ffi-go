[![main](https://github.com/flowerinthenight/clockbound-ffi-go/actions/workflows/main.yml/badge.svg)](https://github.com/flowerinthenight/clockbound-ffi-go/actions/workflows/main.yml)
[![Go Reference](https://pkg.go.dev/badge/github.com/flowerinthenight/clockbound-ffi-go.svg)](https://pkg.go.dev/github.com/flowerinthenight/clockbound-ffi-go)

> [!IMPORTANT]  
> This library is still using the `main-2.0` branch of the [ClockBound daemon](https://github.com/aws/clock-bound/tree/main/clock-bound-d).

## clockbound-ffi-go

A Go client for [aws/clock-bound](https://github.com/aws/clock-bound) using the provided [FFI](https://github.com/aws/clock-bound/tree/main/clock-bound-ffi) (requires [CGO](https://pkg.go.dev/cmd/cgo)).

The [ClockBound daemon](https://github.com/aws/clock-bound/tree/main/clock-bound-d) must be running in order to use this library, as well as the dependencies from the FFI.

```sh
# Rust environment is expected to be installed.
$ git clone --single-branch -b main-2.0 https://github.com/aws/clock-bound
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

A cloud-init [startup script](./startup-aws-asg.sh) is also provided for spinning up an [ASG](https://docs.aws.amazon.com/autoscaling/ec2/userguide/auto-scaling-groups.html) with the ClockBound daemon already setup.

```sh
# Create a launch template. ImageId here is Amazon Linux, default VPC.
# You can remove the "KeyName" line if SSH access is not needed.
# (Added newlines for readability. Might not run when copied as is.)
$ aws ec2 create-launch-template \
  --launch-template-name cbclient-lt \
  --version-description version1 \
  --launch-template-data '
  {
    "UserData":"'"$(cat startup-aws-asg.sh | base64 -w 0)"'",
    "ImageId":"ami-0fe289b44779ce58a",
    "InstanceType":"t3.medium",
    "KeyName":"keyName"
  }'

# Create the ASG; update {target-zone} with actual value:
$ aws autoscaling create-auto-scaling-group \
  --auto-scaling-group-name cbclient-asg \
  --launch-template LaunchTemplateName=cbclient-lt,Version='1' \
  --min-size 1 \
  --max-size 1 \
  --availability-zones {target-zone}

# You can now SSH to the instance. Note that it might take some time before
# ClockBound is running due to the need to build it in Rust. You can wait
# for the `clockbound` process, or tail the startup script output, like so:
$ tail -f /var/log/cloud-init-output.log

# Run the sample code:
# Download the latest release sample from GitHub.
$ tar xvzf cbffisample-{version}-x86_64-linux.tar.gz
$ ./example
2025/01/29 01:39:25 earliest: 2025-01-29T01:39:25.288385857Z
2025/01/29 01:39:25 latest  : 2025-01-29T01:39:25.290784645Z
2025/01/29 01:39:25 range: 2.398788ms
2025/01/29 01:39:25 status: SYNCHRONIZED
...
```

## License

This library is licensed under the [MIT License](./LICENSE).
