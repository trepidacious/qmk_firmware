Enable support, using custom transport (otherwise you must use i2c or soft-serial):

```
SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = custom
```

TODO: The following notes only deal with the matrix transport - this is the most important part, but rgb and encoder information can also be transferred.

Provide implementations of `transport_master_init`, `transport_slave_init`, `transport_master` and `transport_slave`.

The init functions are called from `keyboard_master_setup` and `keyboard_slave_setup`, which are in turn called from `keyboard_split_setup`, which is called from `matrix_init` in `quantum/split_common/matrix.c`. This is the matrix code used by `common_features.mk` when `SPLIT_KEYBOARD` is enabled.

The transport functions work slightly differently, they are both called once per scan in `quantum/split_common/matrix.c` by `matrix_scan` function. In the case of the soft-serial implementation at least:

1. `transport_master` actually performs a transaction (as master) to retrieve data from the slave, and then copies that data into the `matrix` array provided as a parameter. This should match the contents of `matrix` passed to `transport_slave` on the slave side.

2. In `transport_slave`, we just copy the matrix provided into a local matrix array, so it can be sent to the master when we are queried. The actual transport occurs in an interrupt triggered by a hardware signal from the master, and this will send data to the master (matrix and encoder state in a `Serial_s2m_buffer_t`), then receive data (backlight state if feature is enabled, in a `Serial_m2s_buffer_t`).

So essentially the master is asked to perform a transaction once per scan, synchronously. The slave is given the opportunity to see the matrix once per scan, but performs its comms asynchronously in response to the master initiating a transaction. The slave uses an interrupt so needs no synchronisation (assuming matrix scanning doesn't use interrupts), but in a ChibiOS version we might want to use a thread for the slave, polling for data received and then responding, and would need to lock on updating the slave copy of the matrix.

The split code assumes that `MATRIX_ROWS` in `config.h` is the total number of rows between the two halves, i.e. if your split keyboard has 4 rows in each half, then use `MATRIX_ROWS=8`. 

Main thread runs `tmk_core/protocol/chibios/main.c`, which just hammers keyboard_task.
