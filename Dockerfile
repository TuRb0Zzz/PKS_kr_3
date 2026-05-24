
FROM ubuntu:22.04 AS builder


RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /build


COPY . .


RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make -j$(nproc)


RUN cd build && ctest -C Release --output-on-failure

FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /build/build/timetracker /app/timetracker
COPY --from=builder /build/build/tests/unit_tests /app/unit_tests

COPY --from=builder /build/build/tests/scenario_start_stop /app/
COPY --from=builder /build/build/tests/scenario_create_project_task /app/
COPY --from=builder /build/build/tests/scenario_export_csv /app/

CMD ["/app/timetracker"]