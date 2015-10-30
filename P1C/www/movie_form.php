<?php include 'header.php' ?>
<body>
	<h2 class="form_header">Create Movie</h2>
	<form id="create_movie_form" action='create_movie.php' method='GET'>
		<input name="create_movie" type="hidden" value="true"/>
		<div>
	      <label class="form_label">Title: </label><input class="form_input_large" type="text" name="title"/><br/><br/>
	      <label class="form_label">Year: </label><input class="form_input" type="text" name="year"/><br/><br/>
	      <label class="form_label">Rating: </label><input class="form_input" type="text" name="rating"/><br/><br/>
	      <label class="form_label">Company: </label><input class="form_input_large" type="text" name="company"/><br/><br/>
	   </div>
		<input class='form_submit' type='submit' value='Create Movie'/>
	</form>
</body>