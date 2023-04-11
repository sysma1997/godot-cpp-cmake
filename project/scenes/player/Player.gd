extends KinematicBody2D

export var gravity = 60
export var speed = 60

func _physics_process(delta):
	var velocity = Vector2.ZERO
	
	print(is_on_floor())
	if !is_on_floor():
		velocity.y += gravity * delta
	
	velocity.x = Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left")
	
	move_and_collide(velocity.normalized())
