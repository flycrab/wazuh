/*
 * Copyright (C) 2015-2019, Wazuh Inc.
 * May 17, 2019.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation.
 */


#include "options.h"
#include <limits.h>
#include "logcollector/logcollector.h"

const option_set_t options = {
    .syscheck = {
        /* Syscheck checking/usage speed. To avoid large cpu/memory usage, you can specify how much to sleep after generating
        the checksum of X files. The default is to sleep one second per 100 files read. */
        .sleep = {
            .def = 1,
            .min = 0,
            .max = 64
        },
        .sleep_after = { 100, 1, 99999 },
        .rt_delay = { 10, 1, 1000 },                    // Syscheck perform a delay when dispatching real-time notifications so it avoids triggering on some temporary files like vim edits. (ms)
        .max_fd_win_rt = { 256, 1, 1024 },              // Maximum number of directories monitored for realtime on windows
        .max_audit_entries = { 256, 1, 4096 },          // Maximum number of directories monitored for who-data on Linux
        .default_max_depth = { 256, 1, 320 },           // Maximum level of recursivity allowed
        .symlink_scan_interval = { 600, 1, 2592000 },   // Check interval of the symbolic links configured in the directories section
        .file_max_size = { 1024, 0, 4095 },             // Maximum file size for calcuting integrity hashes in MBytes
        .logging = { 0, 0, 2 }                          // Debug options (0: no debug, 1: first level of debug, 2: full debugging). Syscheck (local, server and Unix agent).
    },
    .rootcheck = {
        .sleep = { 50, 0, 1000 }                        // Rootcheck checking/usage speed. The default is to sleep 50 milliseconds per each PID or suspictious port.
    },
    .sca = {
        .request_db_interval = { 5, 0, 60 },            // Security Configuration Assessment DB request interval in minutes. This option sets the maximum waiting time to resend a scan when the DB integrity check fails
        .remote_commands = { 0, 0, 1},                  // Enable it to accept execute commands from SCA policies pushed from the manager in the shared configuration. Local policies ignore this option
        .commands_timeout = { 30, 1, 300}               // Default timeout for executed commands during a SCA scan in seconds
    },
    .remote = {
        .recv_counter_flush = { 128, 10, 999999},       // Remoted counter io flush.
        .comp_average_printout = { 19999, 10, 999999 }, // Remoted compression averages printout.
        .verify_msg_id = { 0, 0, 1 },                   // Verify msg id (set to 0 to disable it).
        .pass_empty_keyfile = { 1, 0, 1 },              // Don't exit when client.keys empty.
        .sender_pool = { 8, 1, 64 },                    // Number of shared file sender threads.
        .request_pool = { 1024, 1, 4096 },              // Limit of parallel request dispatchers.
        .request_timeout = { 10, 1, 600 },              // Timeout to reject a new request (seconds).
        .response_timeout = { 60, 1, 3600 },            // Timeout for request responses (seconds).
        .request_rto_sec = { 1, 0, 60 },                // Retransmission timeout seconds.
        .request_rto_msec = { 0, 0, 999 },              // Retransmission timeout milliseconds.
        .max_attempts = { 4, 1, 16 },                   // Max. number of sending attempts.
        .shared_reload = { 10, 1, 18000 },              // Shared files reloading interval (sec).
        .rlimit_nofile = { 65536, 1024, 1048576 },      // Maximum number of file descriptor that Remoted can open.
        .recv_timeout = { 1, 1, 60 },                   // Maximum time waiting for a client response in TCP (seconds).
        .send_timeout = { 1, 1, 60 },                   // Maximum time waiting for a client delivery in TCP (seconds).
        .nocmerged = { 1, 0, 1 },                       // Merge shared configuration to be broadcasted to agents.
        .keyupdate_interval = { 10, 1, 3600 },          // Keys file reloading latency (seconds).
        .worker_pool = { 4, 1, 16 },                    // Number of parallel worker threads.
        .state_interval = { 5, 0, 86400 },              // Interval for remoted status file updating (seconds). 0 means disabled.
        .guess_agent_group = { 0, 0, 1 },               // Guess the group to which the agent belongs (0. No, do not guess (default), 1. Yes, do guess).
        .group_data_flush = { 86400, 0, 2592000 },      // Cleans residual data from unused groups/multigroups. Minimum number of seconds between cleanings. 0 means never clean up residual data.
        .receive_chunk = { 4096, 1024, 16384 },         // Receiving chunk size for TCP. We suggest using powers of two.
        .buffer_relax = { 1, 0, 2 },                    // Deallocate network buffers after usage (0. Do not deallocate memory, 1. Shrink memory to the reception chunk, 2. Full memory deallocation).
        .tcp_keepidle = { 30, 1, 7200 },                // Time (in seconds) the connection needs to remain idle before TCP starts sending keepalive probes.
        .tcp_keepintvl = { 10, 1, 100 },                // The time (in seconds) between individual keepalive probes.
        .tcp_keepcnt = { 3, 1, 50 },                    // Maximum number of keepalive probes TCP should send before dropping the connection.
        .logging = { 0, 0, 2 }                          // Debug options (0: no debug, 1: first level of debug, 2: full debugging). Remoted (server debug).
    },
    .mail = {
        .strict_checking = { 1, 0, 1 },
        .grouping = { 1, 0, 1 },
        .full_subject = { 0, 0, 1 },
        .geoip = { 1, 0, 1 }
    },
    .auth = {
        .timeout_sec = { 1, 0, INT_MAX },
        .timeout_usec = { 0, 0, 999999},
        .logging = { 0, 0, 2 }
    },
    .client_buffer = {
        .tolerance = { 15, 0, 600 },
        .min_eps = { 50, 1, 1000 },
        .warn_level = { 90, 0, 100 },
        .normal_level = { 70, 0, 99 }
    },
    .client = {
        .state_interval = { 5, 0, 86400 },
        .recv_timeout = { 60, 1, 600 },
        .remote_conf = { 1, 0, 1 },
        .logging = { 0, 0, 2 }
    },
    .logcollector = {
        .loop_timeout = { 2, 1, 120 },
        .open_attempts = { 8, 0, 998 },
        .remote_commands = { 0, 0, 1 },
        .vcheck_files = { 64, 0, 1024 },
        .max_lines = { 10000, 0, 1000000 },
        .max_files = { 1000, 1, 100000 },
        .sock_fail_time = { 300, 1, 3600 },
        .input_threads = { 4, N_MIN_INPUT_THREADS, 128 },
        .queue_size = { 1024, OUTPUT_MIN_QUEUE_SIZE, 220000 },
        .sample_log_length = { 64, 1, 4096 },
        .rlimit_nofile = { 1100, 1024, 1048576 },
        .force_reload = { 0, 0, 1 },
        .reload_interval = { 64, 1, 86400 },
        .reload_delay = { 1000, 0, 30000 },
        .exclude_files_interval = { 86400, 1, 172800 },
        .logging = { 0, 0, 2 }
    },
    .database_output = {
        .reconnect_attempts = { 10, 1, 9999 }
    },
    .exec = {
        .request_timeout = { 60, 1, 3600 },
        .max_restart_lock = { 600, 0, 3600 },
        .logging = { 0, 0, 2 }
    },
    .integrator = {
        .logging = { 0, 0, 2 }
    }
};