<!DOCTYPE html>
<html lang="cs">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="assets/css/variables.css?v=1.0">
        <link rel="stylesheet" href="assets/css/styles_global.css?v=1.0">
        <link rel="stylesheet" href="assets/css/styles_login.css?v=1.0">
        <title>Log-in</title>
    </head>
    <body>
        <div class="container">
            <div class="form-container">
                <header>Přihlášení</header>
                <div class="error-msg" id="login-error"></div>
                <form id="form-login">
                    <input class="input-text" type="text" name="email" id="email" placeholder="email">
                    <input class="input-text" type="password" name="password" id="password" placeholder="heslo">
                    <button class="button-submit" type="submit">Přihlásit se</button>
                </form>
            </div>
        </div>
        <script type="module" src="scripts/app_login.js?v=1.0"></script>
    </body>
</html>