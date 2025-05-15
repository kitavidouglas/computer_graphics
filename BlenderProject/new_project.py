import bpy
import math

# -----------------------------------------------------------------------------
# Helper: Retrieve the newly created object.
# -----------------------------------------------------------------------------
def get_new_object():
    obj = bpy.context.view_layer.objects.active
    if obj is None and bpy.context.selected_objects:
        obj = bpy.context.selected_objects[0]
    if obj is None:
        raise RuntimeError("No object found. Check operator context!")
    return obj

# -----------------------------------------------------------------------------
# Reset Scene and Create a New Collection for the Finishing Scene
# -----------------------------------------------------------------------------
bpy.ops.wm.read_factory_settings(use_empty=True)

project_collection = bpy.data.collections.new("FinishingScene")
bpy.context.scene.collection.children.link(project_collection)

def link_object(obj):
    """Move object to the new collection and unlink from the scene collection."""
    if obj:
        project_collection.objects.link(obj)
        if obj.name in bpy.context.scene.collection.objects:
            bpy.context.scene.collection.objects.unlink(obj)

# -----------------------------------------------------------------------------
# Create a Curved Road Approaching the Finish Line
# -----------------------------------------------------------------------------
bpy.ops.curve.primitive_bezier_curve_add(location=(0, -10, 0))
road_curve = get_new_object()
road_curve.name = "FinishRoadCurve"
road_curve.data.dimensions = '3D'

# Modify control points for a smooth curve
spline = road_curve.data.splines[0]
if len(spline.bezier_points) < 2:
    raise RuntimeError("Bezier curve does not have enough control points!")

spline.bezier_points[0].co = (-5, -10, 0)
spline.bezier_points[0].handle_right = (-2, -8, 0)

spline.bezier_points[1].co = (5, 10, 0)
spline.bezier_points[1].handle_left = (2, 8, 0)

# Create a profile shape (a narrow rectangle) for road extrusion.
bpy.ops.mesh.primitive_plane_add(size=1, location=(0, 0, 0))
road_profile = get_new_object()
road_profile.name = "RoadProfile"
road_profile.scale = (2, 0.1, 1)  # Adjust road width

# Assign the profile as the bevel object to create a 3D road.
road_curve.data.bevel_object = road_profile
road_curve.data.fill_mode = 'FULL'

# Convert the beveled curve to a mesh.
# Convert the beveled curve to a mesh.
bpy.context.view_layer.objects.active = road_curve
road_curve.select_set(True)

depsgraph = bpy.context.evaluated_depsgraph_get()
mesh_data = road_curve.evaluated_get(depsgraph).to_mesh()

# Create a new mesh object
road_mesh_obj = bpy.data.objects.new("RoadMeshObj", mesh_data)
bpy.context.collection.objects.link(road_mesh_obj)

# Remove the curve since we now have a mesh version of the road
bpy.data.objects.remove(road_curve, do_unlink=True)

# Move to the correct collection
link_object(road_mesh_obj)



# Remove the temporary profile safely
if road_profile:
    bpy.data.objects.remove(road_profile, do_unlink=True)

link_object(road_curve)

# -----------------------------------------------------------------------------
# Create a Finishing Line as a Vertical Checkered Banner
# -----------------------------------------------------------------------------
bpy.ops.mesh.primitive_plane_add(size=4, location=(0, 9.5, 0.01))
finish_line = get_new_object()
finish_line.name = "FinishLine"
finish_line.rotation_euler = (math.radians(90), 0, 0)  # Make it vertical
link_object(finish_line)

# Create a new material with a checker texture for the finish line.
finish_mat = bpy.data.materials.new(name="FinishLineMat")
finish_mat.use_nodes = True
nodes = finish_mat.node_tree.nodes
links = finish_mat.node_tree.links

# Add shader nodes
tex_coord_node = nodes.new(type='ShaderNodeTexCoord')
checker_node = nodes.new(type='ShaderNodeTexChecker')
checker_node.inputs['Scale'].default_value = 10  # Adjust density

principled_node = nodes.new(type='ShaderNodeBsdfPrincipled')
output_node = nodes.new(type='ShaderNodeOutputMaterial')

# Connect nodes
links.new(tex_coord_node.outputs['UV'], checker_node.inputs['Vector'])
links.new(checker_node.outputs['Color'], principled_node.inputs['Base Color'])
links.new(principled_node.outputs['BSDF'], output_node.inputs['Surface'])

finish_line.data.materials.append(finish_mat)

# -----------------------------------------------------------------------------
# Position the Main Car at the Finishing Spot
# -----------------------------------------------------------------------------
bpy.ops.mesh.primitive_cube_add(location=(0, 8.5, 0.5))
main_car = get_new_object()
main_car.name = "MainCar"
main_car.scale = (0.75, 1.5, 0.5)
link_object(main_car)

# -----------------------------------------------------------------------------
# Create Opponent Cars Positioned Behind the Main Car
# -----------------------------------------------------------------------------
opponent_positions = [(-1, 7.5, 0.5), (1, 7, 0.5), (-2, 6.5, 0.5)]
for i, pos in enumerate(opponent_positions):
    bpy.ops.mesh.primitive_cube_add(location=pos)
    opp_car = get_new_object()
    opp_car.name = f"OpponentCar_{i}"
    opp_car.scale = (0.75, 1.5, 0.5)
    link_object(opp_car)

# -----------------------------------------------------------------------------
# Set Up the Camera to Capture the Finishing Scene
# -----------------------------------------------------------------------------
bpy.ops.object.camera_add(location=(0, -15, 6), rotation=(math.radians(75), 0, 0))
camera = get_new_object()
camera.name = "FinishingSceneCamera"
link_object(camera)
bpy.context.scene.camera = camera

# -----------------------------------------------------------------------------
# Add a Sun Light to Illuminate the Scene
# -----------------------------------------------------------------------------
bpy.ops.object.light_add(type='SUN', location=(0, -10, 10))
sun = get_new_object()
sun.name = "SunLight"
sun.data.energy = 4  # Increase brightness
link_object(sun)

# -----------------------------------------------------------------------------
# Add Ground Plane
# -----------------------------------------------------------------------------
bpy.ops.mesh.primitive_plane_add(size=30, location=(0, 0, -0.01))
ground = get_new_object()
ground.name = "Ground"
link_object(ground)

# Add a simple material to the ground
ground_mat = bpy.data.materials.new(name="GroundMaterial")
ground_mat.use_nodes = True
ground_mat.node_tree.nodes["Principled BSDF"].inputs["Base Color"].default_value = (0.2, 0.2, 0.2, 1)
ground.data.materials.append(ground_mat)

print("Finishing scene setup complete!")
