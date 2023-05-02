# Episode 13 : Ambiant lightning, Culling and optimization with entity batches (https://youtu.be/X6KjDwA7mZg?list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP)
I struggled with const references in the renderer and i created a HashMap class to make it work

## UPDATE 2 of May, 2023 : I actually made a huge mistake looool, in the Renderer.h, in `render` :
```cpp
TexturedModel const& model = pair.first; // Getting current textured model
RawModel const& rawModel = model.rawModel; // Get current model

std::vector<Entity>& batch = pair.second; // Getting every entity that's using it

for(auto &entity : batch) // Loop all the entities in the batch 
{
  prepareTexturedModel(model); // <------------- HERE
  prepareInstance(entity);

  // render the entity
  glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, 0);
}
```
I'm so freakin dumb the `prepareTexturedModel` is actually called for each entity, which basically means that the whole optimisation system with batches is completely useless, because the goal when you're doing that is that all the model preparation stuff is done for each batch and then each entity stuff is done for each entity (including rendering), but when i called `prepareTexturedModel` for each entity, it's basically like the old (not fancy as thinmatrix said) rendering method, which is not optimized and believe me, i tested, if you `prepareTexturedModel` for each entity and you have like 1000 cubes, it's gonna lag, it lagged for me until i realized this

So this is the updated one :
```cpp
void render(HashMap<TexturedModel, std::vector<Entity>> entities)
	{
		// Looping each entry of the map [TexturedModel] => std::vector<Entity>
		for(Pair<TexturedModel, std::vector<Entity>> pair : entities.getKeySet())
		{
			TexturedModel const& model = pair.first; // Getting current textured model
			RawModel const& rawModel = model.rawModel; // Get current model

			std::vector<Entity>& batch = pair.second; // Getting every entity that's using it

			prepareTexturedModel(model); // <--- This is the right place for this method to be called in
			
			for(auto &entity : batch) // Loop all the entities in the batch 
			{
				//prepareTexturedModel(model); <---- [update 2 of may, 2023], don't put this here 
				prepareInstance(entity);

				// render the entity
				glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, 0);
			}
			
			unbindTexturedModel();
		}
		
	}
```
