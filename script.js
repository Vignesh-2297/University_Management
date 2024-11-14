function validateForm() {
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const errorMessage = document.getElementById('error-message');
    const loginContainer = document.getElementById('login-container');
    const studentDetails = document.getElementById('student-details');
    const studentName = document.getElementById('student-name');
    const studentId = document.getElementById('student-id');
    const attendance = document.getElementById('attendance');
    const cgpa = document.getElementById('cgpa');
    const teacherName = document.getElementById('teacher-name');
    const feedback = document.getElementById('feedback');

    errorMessage.textContent = ''; // Clear previous error messages

    // Simulated student data (in a real application, this would come from a database)
    const studentData = {
        username: 'student',
        password: 'password123',
        name: 'John Doe',
        id: 'S123456',
        attendance: '95%',
        cgpa: '3.8',
        teacherName: 'Mr. Smith',
        feedback: 'Excellent performance in class.'
    };

    // Simple validation
    if (username === '' || password === '') {
        errorMessage.textContent = 'Both fields are required.';
        return false; // Prevent form submission
    }

    // Simulate successful login (replace with actual authentication logic)
    if (username === studentData.username && password === studentData.password) {
        // Hide login form and show student details
        loginContainer.style.display = 'none';
        studentDetails.style.display = 'block';
        studentName.textContent = studentData.name;
        studentId.textContent = studentData.id;
        attendance.textContent = studentData.attendance;
        cgpa.textContent = studentData.cgpa;
        teacherName.textContent = studentData.teacherName;
        feedback.textContent = studentData.feedback;
        return false; // Prevent form submission
    } else {
        errorMessage.textContent = 'Invalid username or password.';
        return false; // Prevent form submission
    }
}

function logout() {
    // Hide student details and show login form
    document.getElementById('login-container').style.display = 'block';
    document.getElementById('student-details').style.display = 'none';
    document.getElementById('loginForm').reset(); // Reset the form
}