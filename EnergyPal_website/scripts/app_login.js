function main(){
    document.getElementById("login-error").hidden = true;
    document.getElementById('form-login').addEventListener('submit', function(event){
        event.preventDefault();

        var email = document.getElementById('email').value;
        var password = document.getElementById('password').value;

        var data = new FormData();
        data.append('email', email);
        data.append('password', password);

        fetch('../actions/auth/action_login.php', { method: 'POST', body: data })
        .then(response => response.json())
        .then(data => {
            if(data.success){
                window.location.href = "dashboard";
            } else {
                document.getElementById("login-error").hidden = false;
                document.getElementById('login-error').innerText = data.error;
            }
        })
        .catch(error => console.error('Error login: ', error));
    });
}

main();