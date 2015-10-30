<?php include 'header.php' ?>
<body>
	<h2>Create Actor</h2>
	<form id="create_actor_form" action='create_person.php' method='GET'>
		<input name="create_person" type="hidden" value="true"/>
		<input name="person_type" type="hidden" value="actor"/>
		<h4>First Name</h4>
		<input type="text" name="first"/>
		<h4>Last Name</h4>
		<input type="text" name="last"/>
		<h4>Sex</h4>
		<input type="text" name="sex"/>
		<h4>DOB</h4>
		<input type="text" name="dob"/>
		<h4>DOD</h4>
		<input type="text" name="dod"/>
		<br/><br/>
		<input type='submit' value='Create Actor'/>
	</form>
	<hr/>
</body>