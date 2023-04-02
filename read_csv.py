import pandas as pd

dynamic = pd.read_csv("dynamic.csv")
static = pd.read_csv("static.csv")
schedule_stat = pd.read_csv("schedule_stat.csv")
schedule_dyn = pd.read_csv("schedule_dyn.csv")

print("dynamic")
for i in range(-1, 9):
    df_filter = (dynamic["threads"] == i)
    print(i, dynamic[df_filter]["time"].mean())

print()
print("static")
for i in range(-1, 9):
    df_filter = (static["threads"] == i)
    print(i, static[df_filter]["time"].mean())

print()
print("schedule static")
for i in range(1, 10):
    df_filter = (schedule_stat["chunk_size"] == i)
    print(i, schedule_stat[df_filter]["time"].mean())
for i in range(10, 100, 10):
    df_filter = (schedule_stat["chunk_size"] == i)
    print(i, schedule_stat[df_filter]["time"].mean())
for i in range(100, 1001, 100):
    df_filter = (schedule_stat["chunk_size"] == i)
    print(i, schedule_stat[df_filter]["time"].mean())

print()
print("schedule dynamic")
for i in range(1, 10):
    df_filter = (schedule_dyn["chunk_size"] == i)
    print(i, schedule_dyn[df_filter]["time"].mean())
for i in range(10, 100, 10):
    df_filter = (schedule_dyn["chunk_size"] == i)
    print(i, schedule_dyn[df_filter]["time"].mean())
for i in range(100, 1001, 100):
    df_filter = (schedule_dyn["chunk_size"] == i)
    print(i, schedule_dyn[df_filter]["time"].mean())
