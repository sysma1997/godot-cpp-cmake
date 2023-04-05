extends Node2D

func _on_Sprite_position_changed(node: Node, new_pos: Vector2):
	print("The position of " + node.name + " is now " + str(new_pos))
