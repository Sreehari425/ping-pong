global update_game_state
global ball_x
global ball_y
global ball_dx
global ball_dy
global paddle1_y
global paddle2_y
global player1_score
global player2_score

section .data
ball_x: dq 100
ball_y: dq 100
ball_dx: dq 2
ball_dy: dq 1
paddle1_y: dq 200
paddle2_y: dq 200
player1_score: dq 0
player2_score: dq 0

section .text
update_game_state:
    ; ball_x += ball_dx
    mov rax, [rel ball_x]
    add rax, [rel ball_dx]
    mov [rel ball_x], rax

    ; ball_y += ball_dy
    mov rax, [rel ball_y]
    add rax, [rel ball_dy]
    mov [rel ball_y], rax

    ; Check paddle collisions first
    call check_paddle_collision

    ; bounce on top (0) and bottom (480)
    mov rax, [rel ball_y]
    cmp rax, 0
    jl .invert_y
    cmp rax, 460  ; 480 - ball size (20)
    jg .invert_y
    
    ; Check if ball goes off screen (reset position and update score)
    mov rax, [rel ball_x]
    cmp rax, -20
    jl .player2_scores
    cmp rax, 640
    jg .player1_scores
    ret

.player1_scores:
    ; Player 1 scores (ball went off right side)
    mov rax, [rel player1_score]
    inc rax
    mov [rel player1_score], rax
    jmp .reset_ball

.player2_scores:
    ; Player 2 scores (ball went off left side)
    mov rax, [rel player2_score]
    inc rax
    mov [rel player2_score], rax
    jmp .reset_ball

.reset_ball:
    ; Reset ball to center
    mov qword [rel ball_x], 320
    mov qword [rel ball_y], 240
    ; Reverse direction
    mov rax, [rel ball_dx]
    neg rax
    mov [rel ball_dx], rax
    ret

.invert_y:
    mov rax, [rel ball_dy]
    neg rax
    mov [rel ball_dy], rax
    ret

check_paddle_collision:
    ; Check left paddle collision
    mov rax, [rel ball_x]
    cmp rax, 30     ; paddle1 x (10) + paddle width (20)
    jg .check_right_paddle
    
    ; Ball is in left paddle x range, check y overlap
    mov rax, [rel ball_y]
    mov rbx, [rel paddle1_y]
    cmp rax, rbx
    jl .check_right_paddle    ; ball top is above paddle top
    
    add rbx, 100    ; paddle height
    cmp rax, rbx
    jg .check_right_paddle    ; ball top is below paddle bottom
    
    ; Collision with left paddle - reverse x direction
    mov rax, [rel ball_dx]
    cmp rax, 0
    jg .check_right_paddle    ; already moving right, no collision
    neg rax
    mov [rel ball_dx], rax
    
.check_right_paddle:
    ; Check right paddle collision
    mov rax, [rel ball_x]
    cmp rax, 590    ; paddle2 x (610) - ball size (20)
    jl .end_collision_check
    
    ; Ball is in right paddle x range, check y overlap
    mov rax, [rel ball_y]
    mov rbx, [rel paddle2_y]
    cmp rax, rbx
    jl .end_collision_check   ; ball top is above paddle top
    
    add rbx, 100    ; paddle height
    cmp rax, rbx
    jg .end_collision_check   ; ball top is below paddle bottom
    
    ; Collision with right paddle - reverse x direction
    mov rax, [rel ball_dx]
    cmp rax, 0
    jl .end_collision_check   ; already moving left, no collision
    neg rax
    mov [rel ball_dx], rax

.end_collision_check:
    ret
