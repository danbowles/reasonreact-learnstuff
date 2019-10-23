type action =
| LogIn(string)
| LogOut
| Settings(bool);

type state = {
  loggedIn: bool,
  settings: bool,
  username: string
};

let initialState = {
  loggedIn: false,
  settings: false,
  username: "",
};

[@react.component]
let make = (_) => {
  let (state, dispatch) = React.useReducer((state, action) =>
    switch (action) {
      | LogIn(username) => { ...state, loggedIn: true, username }
      | LogOut => { ...state, loggedIn: false }
      | Settings(visible) => { ...state, settings: visible }
    }, initialState
  );
  let (username, setUsername) = React.useState(() => "");
  let { loggedIn, settings } = state;
  let onSubmit = (event) => {
    ReactEvent.Mouse.preventDefault(event);
    dispatch(LogIn(username));
  };

  let setUsernameHandler = (event) => {
    setUsername(ReactEvent.Form.target(event)##value);
  };

  <div className="wrapper">
    {
      switch (loggedIn) {
        | (true) => {
          <>
            <div className="heading">
              {React.string("Welcome " ++ username ++ ", you are logged in")}
            </div>
            <button onClick={(_) => dispatch(Settings(!settings))}>
              {
                React.string(switch settings {
                  | true => "Close Settings"
                  | false => "Settings"
                })
              }
            </button>
            <button onClick={(_) => dispatch(LogOut)}>
              {React.string("Log Out")}
            </button>
            {
              switch settings {
                | true => {
                  <div className="headingSmall">
                    {React.string("This is a settings page")}
                  </div>
                }
                | _ => React.null
              }
            }
          </>
        }
        | (false) => {
          <>
            <div className="heading">
              {React.string("Logged Out")}
            </div>
            <form>
              <input 
                name="username"
                onChange={setUsernameHandler}
                value={username}
              />
              <button onClick={onSubmit}>
                {React.string("Log In")}
              </button>
            </form>
          </>
        }
      };
    }
  </div>;
};