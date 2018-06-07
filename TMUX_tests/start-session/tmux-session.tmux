source-file ~/.tmux.conf
split-window -d -v
resize-pane -t 0 -y3
send-keys -t 0 'make run' enter
send-keys -t 1 'vim corr*' enter
send-keys -t 1 ':13' enter 'f,ll'

select-pane -t 1
